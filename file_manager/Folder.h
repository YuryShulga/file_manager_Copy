#pragma once
#include <iostream>
#include <direct.h>
#include <io.h>
#include <fstream>
#include "Computer.h"
#include "File.h"
class Folder
{
private:
    std::string m_current_path;
public:
    Folder(std::string current_path);
    //�������� ���������� ����� - ���������� ������� dir
    void view_content();
    //������� �������� � ������� �����
    void create_subfolder(std::string& name);
    //������� ���� � ������� �����
    void create_file(std::string& name);
};

