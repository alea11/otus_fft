#include "Calculator.hpp"

Calculator::Calculator(int pow) 
{
    _pow = pow;
    _size = 1u << pow;    
    
    _w = std::vector<ComplexDigit>(_size / 2); //массив поворотных множителей, достаточно половины    
    
    InitW();
    
    DirectResult = std::vector<ComplexDigit>(_size);
    BackResult = std::vector<ComplexDigit>(_size);
    
    CreateSwapMasks(_pow);
}

void Calculator::DirectCalc(const std::vector<double>& signal)
{
    // формируем массив результата:  DirectResult    

    //предварительно  - заполняем исходными значениями с переиндексацией (реверс разрядов индекса)
    for (long i = 0; i < _size; i++)
    {
        long idx = BitReverse(i);
        DirectResult[i] = ComplexDigit(signal[idx], 0);
    }        

    CalcFFT(DirectResult);        

    // нормализация 
    for (long i = 0; i < _size; i++)
    {
        DirectResult[i].Divide(_size);
    }
}

void Calculator::BackCalc(const std::vector<ComplexDigit>& spectr)
{
    // формируем массив результата:  BackResult     

    //предварительно  - заполняем исходными значениями с переиндексацией (реверс разрядов индекса)
    // и т.к. обратное преобразование - то во входном и выходном массивах меняем числа на сопряженные  
    for (long i = 0; i < _size; i++)
    {
        long idx = BitReverse(i);
        BackResult[i] = ~spectr[idx];
    }        

    CalcFFT(BackResult);

    for (long i = 0; i < _size; i++)
    {
        BackResult[i].Conjugate();
    }
}
    
void Calculator::CalcFFT(std::vector<ComplexDigit>& arr)
{
    // в цикле (и на разных уровнях) - операция 'бабочка'

    // цикл по уровням (разрядам числа - размера)
    for (int p = 0; p < _pow; p++)
    {
        // маска левой части 'разорванного' битового представления индекса цикла
        long leftmask = 0xfffffffeu << p;

        // установленный плавающий бит варианта с динамической 1 (вариант с плавающим 0 - уже учтен в левой маске)
        long b1 = 0x1u << p;

        // маска правой части 'разорванного' битового представления индекса цикла
        long rightmask = ~(leftmask | b1);

        //маска учитываемой части индекса в расчете индекса поворотного множителя:
        // к-во еденичных разрядов маски - равно номеру уровня
        long wmask = ~(0xffffffffu << p);

        // "инвертированный" уровень
        int invp = _pow - p - 1;

        // цикл по элементам массива (по 2)        
        for (long ii = 0; ii < _size / 2; ii++)
        {
            // индексы 2-х операндов определяем: общий индекс цикла (битовое представление) разрываем в позиции номера уровня.
            // левую часть сдвигаем на 1 позицию влево (в старшую область), в разрыв вставляем бит 0 и 1 (2 варианта - 2 результирующих индекса)

            long idx1 = ((ii << 1) & leftmask) | (ii & rightmask);
            long idx2 = idx1 | b1;

            // индекс поворотного множителя
            // - получаем пересечение идекса цикла с этой маской
            // и сдвигаем влево на invp
            long idxW = (ii & wmask) << invp;

            // пересчет пары элементов по алгоритму "бабочка"
            Butterfly(arr[idx1], arr[idx2], _w[idxW]);
        }
    }
}



void Calculator::Butterfly(ComplexDigit& a, ComplexDigit& b, const ComplexDigit& w)
{
    ComplexDigit t = b * w;
    b = a - t;
    a = a + t;
}

// формирование массива поворотных множителей
void Calculator::InitW()
{
    double pi2 = 2 * pi();
    double delta = pi2 / _size; // иттератор по углам (аргументам) комплексного числа
    
    for (long i = 0; i < _size / 2; i++)
    {
        double arg = delta * i;
        _w[i] = ComplexDigit(-arg);
    }
}

// подготовка масок обмена бит для BitReverse
void Calculator::CreateSwapMasks(int n) 
{
    long fullmask = (01u << n) - 1;

    while (n > 1)
    {
        long low = 0;
        ReverceMask m;

        if (n % 2 == 0)
        {
            n = n / 2;
            m.Offset = n;
        }
        else
        {
            n = (n - 1) / 2;
            m.Offset = n + 1;
        }
        low = (01u << n) - 1;
    
        // размножение маски с учетом сдвигов масок предыдущих уровней
        for(auto im = _swapMasks.rend(); im!=_swapMasks.rbegin(); --im)
        {
            low |= low << (*im).Offset;
        }

        m.Low = low;
        m.Hi = m.Low << m.Offset;
        m.Middle = ~(m.Low | m.Hi) & fullmask;
        _swapMasks.push_back(m);    
    }
}

//инверсия порядка следования бит 
long Calculator::BitReverse(long a)
{
    //цикл по подготовленному массиву масок, количество: ~log(n разр.)
    for (const ReverceMask& m : _swapMasks)    
    {
        a = (a & m.Hi) >> m.Offset | (a & m.Low) << m.Offset | (a & m.Middle);
    }
    return a;
}



