#include "Folder.h"

Folder::Folder(std::string current_path) :
	m_current_path{ current_path }
{
}

void Folder::view_content()
{
	std::string s = m_current_path + "*.*";
	const char* char_str = s.c_str();
	struct _finddata_t c_file;
	intptr_t hFile;
	if ((hFile = _findfirst(char_str, &c_file)) == -1L)
	{
		std::cout << ("Данный каталог пуст\n");
		_findclose(hFile);
	}
	else
	{
		do
		{
			std::cout << c_file.name << std::endl;
		} while (_findnext(hFile, &c_file) == 0);
		_findclose(hFile);
	}
}

void Folder::create_subfolder(std::string& name)
{
	const char* char_name = name.c_str();
	if (_mkdir(char_name) == -1)
	{
		std::cout << "Ошибка при создании папки с названием \"" << name << "\"" << std::endl;
		return;
	}
	std::cout << "создана папка " << name << std::endl;
}

void Folder::create_file(std::string& name)
{
	File d(name);
	d.create_file();
	return;
}
