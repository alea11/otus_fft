cmake_minimum_required(VERSION 3.12)

project(fft)

add_executable(fft
    main.cpp
    Harmonic.hpp
    ComplexDigit.hpp
    Signal.hpp
    Signal.cpp
    Calculator.hpp
    Calculator.cpp
    ReverceMask.hpp
    ArgumentsParser.hpp
    ArgumentsParser.cpp

)

set_target_properties(fft PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)