#pragma once
#include <iostream>
#include <string>
#include <io.h>
#include "Computer.h"
#include "fm_exception.h"

class File
{
private:
    //�������� �����
    std::string m_name_of_the_file;
    //���� � �����
    std::string m_path_of_the_file;
    //���� ���� ���������� ��� ���
    bool m_is_exists;
public:
    //constructor 
    explicit File(std::string path_plus_name);
    //getter ���������� ������ �����
    _fsize_t get_size_of_the_file()const;
    //������� ����(���� �� �� ����������)
    void create_file();

};



