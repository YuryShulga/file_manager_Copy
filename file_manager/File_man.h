#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "File.h"
#include "Folder.h"
#include "Disk.h"
#include "Computer.h"
class File_man
{
public:
	File_man();
	//�������� �������
	void Start();
	//��������� ������� help ����� �������� ������ �� �����
	void help();
	//��������� ��������� �������
	bool processing_choise(std::string choice, Computer& comp);
	//���������� ������ ��������� ������� �� 2 ������ - ������� � �������� �������
	void string_to_tokens(std::vector<std::string>& tokens, std::string& choice);
	//��������� ������� - ���� ���� ���������� � �������� ������� ������� �������
	//���� ��� ���������� ������� 1(���� 1 �� ������ ������������� ���� �������)
	int processing_the_tokens(std::vector<std::string>& tokens);
	//��������� ������� �������� ���������� ������
	void processing_command(int& rezult, std::string second_token, std::string& choice, Computer& comp);
};

