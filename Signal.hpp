#pragma once
#include "Harmonic.hpp"

#include <vector>
#include <stdint.h>

class Signal
{
    long _size;
    double pi() { return atan(1)*4; };  

public:
    std::vector<double> Points;
    Signal(long size);
    Signal();
    void ApplyHarmonic(const Harmonic& harm);
};

