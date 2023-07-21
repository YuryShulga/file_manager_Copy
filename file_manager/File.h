#pragma once
#include <iostream>
#include <string>
#include <io.h>
#include "Computer.h"
#include "fm_exception.h"

class File
{
private:
    //название файла
    std::string m_name_of_the_file;
    //путь к файлу
    std::string m_path_of_the_file;
    //флаг файл существует или нет
    bool m_is_exists;
public:
    //constructor 
    explicit File(std::string path_plus_name);
    //getter возвращает размер файла
    _fsize_t get_size_of_the_file()const;
    //создать файл(если он не существует)
    void create_file();

};



