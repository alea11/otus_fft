#pragma once

#include "ComplexDigit.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class StorageOperations
{
public:
    static bool Load(const  std::string& filename, std::vector<double>& values);
    static void Save(const  std::string& filename, const std::vector<double>& values);
    static void Save(const  std::string& filename, const std::vector<ComplexDigit>& values, bool expMode);
};




