#pragma once
#include <iostream>
#include <direct.h>
#include <io.h>
#include <fstream>
#include "fm_exception.h"
#include "File.h"
class Disk
{
private:
    std::string m_current_path;
public:
    Disk(std::string current_path);
    //�������� ���������� �����
    void view_content();
    //������� �������� � ������� �����
    void create_subfolder(std::string& name);
    //������� ���� � ������� �����
    void create_file(std::string& name);

};

