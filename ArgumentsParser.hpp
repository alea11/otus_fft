#pragma once
#include <string>

class ArgumentsParser
{
    int _argc; 
    char** _argv;
public:
    ArgumentsParser(int argc, char* argv[]) : _argc{argc}, _argv{argv}
    {}
    //template<typename T> int GetParam(const char* paramkey, T& value);
    int GetParam(const char* paramkey, std::string& value);
    int GetParam(const char* paramkey, int& value);
    int GetParam(const char* paramkey, bool& value);
private:
    int GetArgPos(const char* paramkey);
};

/*
template<typename T> int ArgumentsParser::GetParam(const char* paramkey, T& value)
{
    int i = 1;
    
    while(i < argc)
    {
        std::string arg{ _argv[i++] };
        if(arg == paramkey)
        {
            if(typeid(T) == typeid(bool))
            {
                value = true;
                return 0;
            }
            else 
            {
                if(i>=argc)
                    return -1; // error
                if(typeid(T) == typeid(int))
                {
                    value = std::stoi(_argv[i++]);
                }
                else if(typeid(T) == typeid(std::string))
                {
                    value = _argv[i++];
                }
                return 0;
            }
            
        }
    }

    if(typeid(T) == typeid(bool))
    {
        value = false;
        return 0;
    }
    
    return -1; // error Неизвестный параметр

    
}
    */