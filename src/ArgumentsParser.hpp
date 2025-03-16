#pragma once
#include <string>

class ArgumentsParser
{
    int _argc; 
    char** _argv;
public:
    ArgumentsParser(int argc, char* argv[]) : _argc{argc}, _argv{argv}
    {}
    int GetParam(const char* paramkey, std::string& value);
    int GetParam(const char* paramkey, int& value);
    int GetParam(const char* paramkey, bool& value);
private:
    int GetArgPos(const char* paramkey);
};
