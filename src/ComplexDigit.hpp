#pragma once
#include	<cmath>

class ComplexDigit
{
public:
    double Re;
    double Im;

public:
    ComplexDigit()
    {
        Re = 0;
        Im = 0;
    }
    ComplexDigit(double re, double im)
    {
        Re = re;
        Im = im;
    }

    // создание нормированного комплексного числа, с модулем = 1 и аргументом в диапазоне 0...2Pi
    ComplexDigit(double arg)
    { 
        double module = 1;
        Re = module * cos(arg);
        Im = module * sin(arg);
    }

    double GetModule() const
    { return sqrt(Re * Re + Im * Im); } 

    double GetArgument() const
    { return atan2(Im, Re); }

    // Сопряжение
    void Conjugate()
    {
        Im *= -1;
    }
        
    // Деление
    void Divide(double d)
    {
        Re /= d;
        Im /= d;
    }

    
};

inline ComplexDigit operator +(const ComplexDigit& a, const ComplexDigit& b)
{         
    return {a.Re + b.Re, a.Im + b.Im};
}

inline ComplexDigit operator -(const ComplexDigit& a, const ComplexDigit& b)
{
    return {a.Re - b.Re, a.Im - b.Im};
}

inline ComplexDigit operator *(const ComplexDigit& a, const ComplexDigit& b)
{
    return {a.Re * b.Re - a.Im * b.Im, a.Re * b.Im + a.Im * b.Re};
}

inline ComplexDigit operator *(const ComplexDigit& a, double mul)
{
    return {a.Re * mul, a.Im * mul};
}

// Получение сопряженного комплексного числа           
inline ComplexDigit operator ~(const ComplexDigit& a)
{
    return {a.Re ,  a.Im * -1};
}

inline ComplexDigit operator /(const ComplexDigit& a, const ComplexDigit& b)
{
    double divider = b.Re * b.Re + b.Im * b.Im;
    return a * (~b) / divider;
}

inline ComplexDigit operator /(const ComplexDigit& a, double d)
{
    return {a.Re/d, a.Im/d};
}

        
