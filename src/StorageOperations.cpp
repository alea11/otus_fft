#include "StorageOperations.hpp"


bool StorageOperations::Load(const  std::string& filename, std::vector<double>& values)
{
    std::cout << "Loading ..." << std::endl;
    std::ifstream in_file{ filename }; // открываем файл на перезапись
    if (!in_file.is_open()) 
    {
        std::cout << "Failed to open file: " << filename << "!" << std::endl;      
        return false;  
    }
    else
    {
        double x;
        while (in_file >> x )
        {
            values.push_back(x);
        }
        in_file.close();
        std::cout << "... success"  << std::endl; 
        return true;
    }
}



void StorageOperations::Save(const  std::string& filename, const std::vector<double>& values)
{
    std::cout << "Saving ..." << std::endl;
    std::ofstream out_file{ filename, std::ios_base::trunc }; // открываем файл на перезапись
    if (!out_file.is_open()) 
    {
        std::cout << "Failed to open file for write: " << filename << "!" << std::endl;        
    }
    else
    {
        for (const double value : values)
        {
            out_file << value << std::endl;
        }
        out_file.close();
        std::cout << "... success"  << std::endl;
    }

}

void StorageOperations::Save(const  std::string& filename,  const std::vector<ComplexDigit>& values, bool expMode) 
{
    std::cout << "Saving ..." << std::endl;
    std::ofstream out_file{ filename, std::ios_base::trunc }; // открываем файл на перезапись
    if (!out_file.is_open())
    {
        std::cout << "Failed to open file for write: " << filename << "!" << std::endl;
    }
    else
    {
        if (expMode)
        {
            for (  const ComplexDigit& value : values)
            {
                out_file << value.GetModule() << " " << value.GetArgument() << std::endl;
            }
        }
        else
        {
            for (const ComplexDigit& value : values)
            {
                out_file << value.Re << " " << value.Im << std::endl;
            }
        }
        
        out_file.close();
        std::cout << "... success"  << std::endl;
    }
}