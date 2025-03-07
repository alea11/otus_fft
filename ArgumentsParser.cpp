#include "ArgumentsParser.hpp"



int ArgumentsParser::GetParam(const char* paramkey, std::string& value)
{
    int pos = GetArgPos(paramkey);
    if (pos < _argc-1)
    {
        value = _argv[pos+1];
        return 0;
    }
    return -1;    
}

int ArgumentsParser::GetParam(const char* paramkey, int& value)
{
    int pos = GetArgPos(paramkey);
    if (pos < _argc-1)
    {
        value = std::stoi(_argv[pos+1]);
        return 0;
    }
    return -1;
}

int ArgumentsParser::GetParam(const char* paramkey, bool& value)
{
    int pos = GetArgPos(paramkey);
    if (pos < _argc)
    {
        value = true;
        return 0;
    }
    value = false;
    return -1;

}

int ArgumentsParser::GetArgPos(const char* paramkey)
{
    int i = 1;

    while (i < _argc)
    {
        std::string arg{ _argv[i] };
        if (arg == paramkey)
        {
            break;
        }
        i++;
    }
    return i;
}



