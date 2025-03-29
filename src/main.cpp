

#include <string>
#include <vector>
#include <iostream>

#include "Harmonic.hpp"
#include "ComplexDigit.hpp"
#include "Signal.hpp"
#include "Calculator.hpp"
#include "ArgumentsParser.hpp"
#include "StorageOperations.cpp"

void InputHarmonics(std::vector<Harmonic>& harmonics, long size);


const std::string SignalFName("Signal");
const std::string SpetrResFName("SpetrRes");
const std::string SignalResFName("SignalRes");

int main(int argc, char* argv[]) 
{
    const int minPow = 8;
    const int maxPow = 22;
    int pow =0;
    long size = 0;
    Signal signal;

    ArgumentsParser ap (argc, argv);
    std::string fname;
    if (ap.GetParam("-signalFName", fname) == 0 &&  StorageOperations::Load(fname, signal.Points))
    {        
        long s = signal.Points.size();
        std::cout << " s " <<  s << std::endl;
        while (s > 0)
        {
            s = s >> 1;
            pow ++;
        }
        pow--;       

        std::cout << " pow "  << pow << std::endl;
    }
    else
    {
        std::cout << "Hi. The number of signal samples is a power of two. Enter the power, between " << minPow << " and " << maxPow << std::endl;

        std::cin >> pow;
        if (std::cin.fail())        
            std::cout << "Bad value!" << std::endl;        
        else if(pow < minPow || pow > maxPow)
            std::cout << "entered value: " <<  pow << " - out of range" << std::endl;
        else
        {
            size = 1 << pow;
            std::cout << "entered: pow: " <<  pow << ", number of counts: " << size << std::endl;

            signal =  Signal(size);
            std::vector<Harmonic> harmonics;
            InputHarmonics(harmonics, size);
            
            if(!harmonics.empty())
            {
                std::cout << "Entered harmonics: " <<  std::endl;
                for (const Harmonic& harm : harmonics) 
                {
                    std::cout << "Period: "  << harm.Period << ", Amplitude: " << harm.Amplitude  << ", Phase: " << harm.Phase <<  std::endl;
                }
                
                // формируем сигнал из гармоник. ( можно формировать и другим способом, напр. вводом конкретных значений, не обязательно гармонических функций) 
                for (const Harmonic& harm : harmonics)
                {                    
                    signal.ApplyHarmonic(harm);                                               
                }                
            }
        }
    }

    if(signal.Points.empty())
    {
        std::cout << "signal not set." <<  std::endl;            
    }
    else
    {
        char c = 'n';
        std::cout << "if you want to save signal - press 'y'" <<  std::endl;

        std::cin.clear();
        std::cin.ignore(222222, '\n');
        std::cin >> c;        

        if(c == 'Y' || c == 'y')        
            StorageOperations::Save(SignalFName, signal.Points);        
        
        Calculator calc(pow);

        // преобразование в спектр
        calc.DirectCalc(signal.Points);
        
        c = 'n';
        std::cout << "if you want to save result of Direct FFT - press 'y'" <<  std::endl;
        std::cin.clear();
        std::cin.ignore(222222, '\n');
        std::cin >> c;
        if(c == 'Y' || c == 'y')
            StorageOperations::Save(SpetrResFName, calc.DirectResult, true);
                
        //обратное преобразование (из спектра в сигнал)
        calc.BackCalc(calc.DirectResult);
        c = 'n';
        std::cout << "if you want to save result of Back FFT - press 'y'" <<  std::endl;
        std::cin.clear();
        std::cin.ignore(222222, '\n');
        std::cin >> c;
        if(c == 'Y' || c == 'y')
            StorageOperations::Save(SignalResFName, calc.BackResult, false);
    }
        
    std::cout << "To exit, press 'Enter'" << std::endl;
    std::cin.clear();
    std::cin.ignore(222222, '\n');
    std::cin.get();
    
    return 0;
}

template<typename T> bool inpValue(T& val)
{
    std::cin >> val;
    if(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore();
        return false;
    }
    return true;
}

void InputHarmonics(std::vector<Harmonic>& harmonics, long size)
{
    int cnt = 1;
    bool constCompAdded = false;
    std::cout << "start entering harmonics:"  << std::endl;
    
    // цикл ввода гармоник сигнала. Выход - ввод не числа
    while(1)
    {        
        Harmonic harm;
        
        if(!constCompAdded)
            std::cout << "Enter Period (double) for harmonic "  << cnt << ", less than " << size << " (if 0 then a constant component is specified)" <<  std::endl;
        else
            std::cout << "Enter Period (double) for harmonic "  << cnt << ", greater than 1, less than " << size << std::endl;
        if( !inpValue(harm.Period))
            break;
        if((constCompAdded && harm.Period < 2) || harm.Period > size)
        {
            std::cout << "Incorrect input" << std::endl;
            continue;
        }        

        std::cout << "Enter Amplitude (double) for harmonic "  << cnt <<  std::endl;
        if( !inpValue(harm.Amplitude))
            break;
        if(harm.Period != 0)
        {
            std::cout << "Enter Phase (double) for harmonic "  << cnt <<  std::endl;
            if( !inpValue(harm.Phase))
                break;
        }
        else
        {
            constCompAdded = true;
        }
        
        harmonics.push_back(harm);        
        cnt++;
    } 
}

