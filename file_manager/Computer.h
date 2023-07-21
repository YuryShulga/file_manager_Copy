#pragma once
#include <iostream>
#include <vector>
#include <windows.h>//��������� �� ������ �������� ���������� ������ � ����������
#include <algorithm>
#include <string>
#include <filesystem>//����� �++17 �� std::filesystem::copy
#include "File.h"
#include "Disk.h"
#include "Folder.h"
#include "fm_exception.h"

#include <fstream>

class Computer
{
private:
	std::vector<std::string> m_list_of_disks;//������ ������ � ��������� � �������
	//������� ���� ��� �������� ������������
	std::string m_current_path;
	//1=���� ������������ � ����� ���� �����
	bool m_is_in_folder;
	//-----------
	void find_disks();//�������������� ������ ������������ Computer();
public:
	//constructor
	explicit Computer();
	//setters
	void set_current_path(std::string path);
	void set_is_in_folder(bool flag);
	//getters
	std::string get_current_path();
	std::string get_item_of_list_of_disks(int index)const;
	bool get_is_in_folder()const;
	size_t get_m_list_of_disks_size()const;
	std::vector<std::string> get_m_list_of_disks()const;
	//������������ ������ �� ������ ��������� � ������ ����������
	std::string to_string()const;
	//�������� ���������� �����/�����/����� - ��������� ������� dir
	void view_content();
	//�������� ������ ���������
	void update_the_disk_list();
	//���������� ����������  �� ���� � ������ �� ������ � �������(������ ���� ��� ������ ��������)
	bool is_the_path_is_full(std::string path);
	//�������� ��������� �� ���� �� ����� - ���������� 1 ���� �����
	bool is_the_folder_at_path(std::string path);
	//������� ���� �� ������ �� ����
	bool is_object_exist(std::string path);
	//���������� ������� ������� ������ � ������� �������
	void to_upper(std::string& str);
	//�������� �������� �� ������������ � ����� �����(�������� �:\)
	bool located_in_the_disk_root();
	//���������� ��������� �� �� � �����(2 ������)
	void parameters_to_tokens(std::string parameters, std::string& old_name, std::string& new_name);
	//���������� �� ������� �� ����+��
	std::string get_object_name(std::string path);
	//���������� ���� ������� �� ����+��
	std::string get_object_path(std::string path);
	//-------------------
	//��������� ������� dir(�������� ����������� �����/�����)
	void do_dir();
	//��������� ������� cd + ����
	void cd_path(std::string path);
	//������� cd.. ����� �� �����(�� ������� ����)
	void cd_out();
	//������� ������� �����
	void create_dir(std::string second_token);
	//��������� ������� ������� ����
	void create_file_processing(std::string second_token);
	//��������� ������� ������� ����� ��� ����
	void delete_folder_or_file(std::string path);
	//�������������� ������ ������� �����/�����
	void delete_sub_function(std::string path);
	//������� �������������/����������� ����� ��� ���� //���� ��� �� ������� 1, ���� ��� 0 
	bool rename_file_or_folde(std::string parameters);
	//������� ���������� ����� ��� ����
	void copy_file(std::string parameters);

};

