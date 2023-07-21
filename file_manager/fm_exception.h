#pragma once
#include <iostream>
class fm_exception :
    public std::exception
{
private:
    std::string m_message;
public:
    fm_exception(std::string msg);
    std::string what();
};

