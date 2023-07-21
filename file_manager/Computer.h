#pragma once
#include <iostream>
#include <vector>
#include <windows.h>//использую дл¤ поиска названий логических дисков в компьютере
#include <algorithm>
#include <string>
#include <filesystem>//нужен с++17 дл¤ std::filesystem::copy
#include "File.h"
#include "Disk.h"
#include "Folder.h"
#include "fm_exception.h"

#include <fstream>

class Computer
{
private:
	std::vector<std::string> m_list_of_disks;//массив дисков и устройств в системе
	//текущий путь где находитс¤ пользователь
	std::string m_current_path;
	//1=если пользователь в какой либо папке
	bool m_is_in_folder;
	//-----------
	void find_disks();//вспомогательна¤ функци¤ конструктора Computer();
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
	//формирование строки из списка устройств и дисков компьютера
	std::string to_string()const;
	//показать содержимое файла/папки/диска - реализаци¤ команды dir
	void view_content();
	//обновить список устройств
	void update_the_disk_list();
	//возвращает начинается  ли путь с одного из дисков в системе(полный путь или только название)
	bool is_the_path_is_full(std::string path);
	//проверка указывает ли путь на папку - возвращает 1 если папка
	bool is_the_folder_at_path(std::string path);
	//провер¤ю есть ли объект по пути
	bool is_object_exist(std::string path);
	//приведение первого символа строки в верхний регистр
	void to_upper(std::string& str);
	//провер¤ет находитс¤ ли пользователь в корне диска(например с:\)
	bool located_in_the_disk_root();
	//разлаживаю параметры на до и после(2 токена)
	void parameters_to_tokens(std::string parameters, std::string& old_name, std::string& new_name);
	//возвращает им¤ объекта из путь+им¤
	std::string get_object_name(std::string path);
	//возвращает путь объекта из путь+им¤
	std::string get_object_path(std::string path);
	//-------------------
	//обработка команды dir(просморт содержимого папки/диска)
	void do_dir();
	//обработка команды cd + путь
	void cd_path(std::string path);
	//команда cd.. выход из папки(на уровень выше)
	void cd_out();
	//команда создать папку
	void create_dir(std::string second_token);
	//обработка команды создать файл
	void create_file_processing(std::string second_token);
	//обработка команды удалить папку или файл
	void delete_folder_or_file(std::string path);
	//вспомогательна¤ функци¤ удалени¤ файла/папки
	void delete_sub_function(std::string path);
	//команда переименовать/переместить папку или файл //если все ок возврат 1, если нет 0 
	bool rename_file_or_folde(std::string parameters);
	//команда копировать папку или файл
	void copy_file(std::string parameters);

};

