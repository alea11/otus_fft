cmake_minimum_required(VERSION 3.12)

project(fft)

add_executable(fft
    src/main.cpp
    src/Harmonic.hpp
    src/ComplexDigit.hpp
    src/Signal.hpp
    src/Signal.cpp
    src/Calculator.hpp
    src/Calculator.cpp
    src/ReverceMask.hpp
    src/ArgumentsParser.hpp
    src/ArgumentsParser.cpp

)

set_target_properties(fft PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)