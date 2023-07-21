#include "File.h"


File::File(std::string path_plus_name)
{
	Computer comp;
	//проверка файл существует или нет
	if (comp.is_object_exist(path_plus_name))
		m_is_exists = true;
	else
		m_is_exists = false;
	m_name_of_the_file = comp.get_object_name(path_plus_name);
	m_path_of_the_file = comp.get_object_path(path_plus_name);
}

_fsize_t File::get_size_of_the_file() const
{
	const char* s = m_name_of_the_file.c_str();
	struct _finddata_t* file_info = new _finddata_t;
	_findfirst(s, file_info);
	_fsize_t size = file_info->size;
	delete file_info;
	return size;
}

void File::create_file()
{
	if (m_is_exists)
	{//файл уже существует
		throw fm_exception("файл с таким именем уже существует");
		return;
	}
	//создаю файл с названием name
	std::ofstream out(m_path_of_the_file+m_name_of_the_file);
	if (!out.is_open())
	{
		throw fm_exception("ошибка при создании файла(std::ofstream out(name))");
		return;
	}
	out.close();
	m_is_exists = true;

}
