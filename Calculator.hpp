#pragma once

#include "ComplexDigit.hpp"
#include "ReverceMask.hpp"

#include <vector>
//#include <stdint.h>

class Calculator
{
    int _pow;
    long _size;
    std::vector<ComplexDigit> _w; //поворотные коэффициенты
    std::vector<ReverceMask> _swapMasks; //битовые маски инверсии разрядов чисел

public:    
    std::vector<ComplexDigit> DirectResult; //результат прямого преобразования
    std::vector<ComplexDigit> BackResult; //результат обратного преобразования

private:    
    void InitW();
    void CalcFFT(std::vector<ComplexDigit>& arr);
    void Butterfly(ComplexDigit& a, ComplexDigit& b, const ComplexDigit& w);
    void CreateSwapMasks(int n);
    long BitReverse(long a);
    double pi() { return atan(1) * 4; };

public:
    Calculator(int pow);
    void DirectCalc(const std::vector<double>& signal);
    void BackCalc(const std::vector<ComplexDigit>& spectr);
};