
#include "Signal.hpp"
#include <cmath>

Signal::Signal()
{
    _size = 0;
    Points = std::vector<double>(0); 
}

Signal::Signal(long size)
{
    _size = size;
    Points = std::vector<double>(size);    
}

// добавление очередной гармоники к сигналу
void Signal::ApplyHarmonic(const Harmonic& harm)
{    
    if(harm.Period < 2) // т.е. постоянная составляющая
    {
        auto iter { Points.begin()}; // получение иттератора
        while(iter != Points.end() )
        {
            *iter += harm.Amplitude;
            ++iter;
        }        
    }
    else
    {        
        double pi2 = 2 * pi();
        double delta = pi2 / harm.Period; // иттератор по отметкам времени периодического сигнала

        double ph = harm.Phase;        
        if(ph > pi2)
        {
            // нормируем фазу
            ph = fmod(ph, pi2);
        }

        // построение синусойды с соответствующим периодои
        for (long i = 0; i < _size; i++)
        {
            Points[i] += harm.Amplitude * sin(delta * i + ph);
        }
        
    }

}



