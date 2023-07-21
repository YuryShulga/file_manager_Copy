#include "Computer.h"

Computer::Computer() :
	//m_size{ 0 },
	m_current_path{ "computer" },
	m_is_in_folder{ false }
{
	//������ �������� ���������� ����� � ����������� ������ �� � ������ m_disks; 
	find_disks();
}

void Computer::find_disks()
{
	DWORD mydrives = 1000;// buffer length
	char buf[10000]{};// buffer for drive string storage
	GetLogicalDriveStrings(mydrives, (LPWSTR)buf);
	for (int i = 0; i < 100; i++)
	{
		if (buf[i] == ' ')
			break;
		//��� � ������� ���������� �� ������� 
		//GetLogicalDriveStrings �������� �����  
		if (buf[i] >= 65 && buf[i] <= 90)
		{
			//�������� �������� ����� � ������ ������ 
			std::string new_disk;
			new_disk = buf[i];
			new_disk += ":\\";
			m_list_of_disks.push_back(new_disk);
		}

	}
}

std::string Computer::to_string() const
{
	std::string s;
	for (size_t i = 0; i < m_list_of_disks.size(); i++)
	{
		s += m_list_of_disks[i] + "  ";
	}
	return s;
}

void Computer::view_content()
{
	//�������� ������ ��������� � ������
	update_the_disk_list();
	//������ ������ ��������� � ������
	std::cout << "������ ��������� ������ � ��������� ����������:" << std::endl;
	std::cout << to_string() << std::endl;
}

std::string Computer::get_current_path()
{
	return m_current_path;
}

void Computer::set_current_path(std::string path)
{
	m_current_path = path;
}

std::string Computer::get_item_of_list_of_disks(int index) const
{
	return m_list_of_disks[index];
}

bool Computer::get_is_in_folder() const
{
	return m_is_in_folder;
}

size_t Computer::get_m_list_of_disks_size() const
{
	return m_list_of_disks.size();
}

std::vector<std::string> Computer::get_m_list_of_disks() const
{
	return m_list_of_disks;
}

void Computer::set_is_in_folder(bool flag)
{
	m_is_in_folder = flag;
}

void Computer::update_the_disk_list()
{

	m_list_of_disks.clear();
	find_disks();
}

void Computer::delete_folder_or_file(std::string path)
{
	//��������� � path ������� ������ ���� ��� ������ ��������
	if (is_the_path_is_full(path))
		//���� ������� ������ ���� 
	{
		//������� ������� ������
		delete_sub_function(path);
		return;
	}
	//����� path ������ ����� � ������� ��� comp �����
	path = m_current_path + path;
	//������� ������� ������
	delete_sub_function(path);
	return;

}

bool Computer::is_the_path_is_full(std::string path)
{
	//���� ����� path ������ 4 � ������ ������ ��������� �������� ������� ������ � ������� �������
	if (path[1] == ':')
		to_upper(path);
	for (size_t i = 0; i < m_list_of_disks.size(); i++)
	{
		if (path[0] == m_list_of_disks[i][0] &&
			path[1] == m_list_of_disks[i][1] &&
			path[2] == m_list_of_disks[i][2])
		{
			return true;
		}
	}
	return false;
}

bool Computer::is_the_folder_at_path(std::string path)
{
	//������ ���������� path ��� ������� ������� 
	//��������� ���������
	const char* char_path = path.c_str();
	if (_chdir(char_path) == 0)
		return 1;
	else return 0;
}

bool Computer::is_object_exist(std::string path)
{
	const char* char_str = path.c_str();
	struct _finddata_t c_file;
	intptr_t hFile;
	if ((hFile = _findfirst(char_str, &c_file)) == -1L)
	{
		_findclose(hFile);
		return 0;
	}
	else
	{
		_findclose(hFile);
		return true;
	}
}


void Computer::to_upper(std::string& str)
{
	std::string s;
	s.push_back(str[0]);
	std::transform(s.begin(), s.end(), s.begin(), ::toupper);
	str[0] = s[0];
}

void Computer::do_dir()
{
	//���� ������������ ��������� � ����� ����������
	if (m_current_path == "computer")
	{
		view_content();
		return;
	}
	//���� ������������ ��������� � ����� �����
	if (located_in_the_disk_root())
	{
		Disk disk(m_current_path);
		disk.view_content();
		return;
	}
	//���� ������������ ��������� � �����
	if (m_is_in_folder)
	{
		Folder folder(m_current_path);
		folder.view_content();
		return;
	}
}

bool Computer::located_in_the_disk_root()
{
	for (size_t i = 0; i < m_list_of_disks.size(); i++)
	{
		//���� ������� ������������ ��������� � ��������� ������ �� ��������� � �������
		if (m_current_path == m_list_of_disks[i])
		{
			return true;
		}
	}
	return false;
}

void Computer::parameters_to_tokens(std::string parameters, std::string& old_name, std::string& new_name)
{
	bool fraction_sign_is_on = false;
	for (size_t i = 0; i < parameters.size(); i++)
	{
		if (parameters[i] == '/')
		{
			if (fraction_sign_is_on == false)
			{
				fraction_sign_is_on = true;
				continue;
			}


		}
		if (fraction_sign_is_on)
			//��������� ������ �����
		{
			new_name.push_back(parameters[i]);
		}
		else
			//��������� ������ �����
		{
			old_name.push_back(parameters[i]);
		}
	}
}

std::string Computer::get_object_name(std::string path)
{
	std::string name;
	while (path.size() != 0)
	{
		if (path[path.size() - 1] != '\\')
		{
			name.insert(name.begin(), path[path.size() - 1]);
			path.pop_back();
		}
		else
			break;
	}
	return name;
}

std::string Computer::get_object_path(std::string path)
{
	while (path.size() != 0)
	{
		if (path[path.size() - 1] != '\\')
		{
			path.pop_back();
		}
		else
			break;
	}
	return path;
}

void Computer::cd_path(std::string path)
{
	//�������� ������ ������ 
	update_the_disk_list();
	//��� ���������� ������������ ������/��������� � ���������� ���������(path)
	for (std::string item : m_list_of_disks)
	{
		//���� �������� ����� � ����� �: d:
		if (path.size() == 2)
		{
			std::string ss = item;//�������� ������������� ����� ������������������ � ������ ������
			//std::string ss1 = item;
			std::string s_path = path;//��������� ���� ����������������� � ������ �������
			std::transform(s_path.begin(), s_path.end(), s_path.begin(), ::tolower);
			std::transform(ss.begin(), ss.end(), ss.begin(), ::tolower);
			ss.pop_back();
			if (ss == s_path || item == path)
			{
				//���� ����������
				m_current_path = item;
				m_is_in_folder = false;
				return;
			}
		}
		if (path.size() == 3)
		{
			std::string ss = item;//�������� ������������� ����� ������������������ � ������ ������
			//std::string ss1 = item;
			std::string s_path = path;//��������� ���� ����������������� � ������ �������
			std::transform(s_path.begin(), s_path.end(), s_path.begin(), ::tolower);
			std::transform(ss.begin(), ss.end(), ss.begin(), ::tolower);
			if (ss == s_path || item == path)
			{
				//���� ����������
				m_current_path = item;
				m_is_in_folder = false;
				return;
			}
		}
	}
	// ---------------
	//���� �������� �������� �����(��� ����)
	std::string s;
	const char* char_str;
	struct _finddata_t c_file;
	intptr_t hFile;
	if (!is_the_path_is_full(path))
	{
		s = m_current_path + path;
		char_str = s.c_str();
		//���� �� �����
		if ((hFile = _findfirst(char_str, &c_file)) == -1L)
		{
		}
		//���� ����� ����� 
		else
		{

			m_current_path = m_current_path + c_file.name + "\\";
			_findclose(hFile);
			m_is_in_folder = true;
			return;
		}
	}
	//--------------------
	//���� ������� ���� � �������� �����
	if (is_the_path_is_full(path))
	{
		s = path;
		char_str = s.c_str();
		//���� �� ����� �����
		if ((hFile = _findfirst(char_str, &c_file)) == -1L)
		{
			_findclose(hFile);
		}
		//���� ����� ����� 
		else
		{

			if (path[1] == ':' && path[2] == '\\')//������ ���� � "�: d:"(��������� �����)
			{
				std::string s_path;
				s_path += path[0];
				std::transform(s_path.begin(), s_path.end(), s_path.begin(), ::toupper);
				path[0] = s_path[0];
				m_current_path = path + '\\';
				_findclose(hFile);
				if (!m_is_in_folder)
					m_is_in_folder = true;
				return;
			}
			else if (path[1] == ':')
			{
				std::cout << "����� �����(���� ����) \"" << path << "\" �� �������(�)\n";
				return;
			}
			m_current_path = m_current_path + c_file.name + "\\";
			_findclose(hFile);
			m_is_in_folder = true;
			return;
		}
	}
	//----------------

	std::cout << "����� �����(���� ����) \"" << path << "\" �� �������(�)\n";
}

void Computer::cd_out()
{
	//���� ������� �������������� "computer"
	if (m_current_path == "computer")
	{
		std::cout << "��������� �� ������� ���� ����������" << std::endl;
		return;
	}
	//���� ������� �������������� "������ �����"
	if (!m_is_in_folder)
	{
		m_current_path = "computer";
		return;
	}
	//���� ������� �������������� "�����"
	std::string path = m_current_path;
	path.pop_back();
	for (auto item = path.rbegin(); *item != '\\'; item++)
		path.pop_back();
	if (path.size() == 3)
	{
		m_is_in_folder = false;
		m_current_path = path;
		return;
	}
	m_current_path = path;
}

void Computer::create_dir(std::string second_token)
{
	std::string new_folder = m_current_path + second_token;
	//���� �������������� � ����������
	if (m_current_path == "computer")
	{
		std::cout << "� ������ ����� ���������� ������� ����� �����" << std::endl;
		return;
	}
	//���� �������������� � ����� �����
	if (m_current_path.size() == 3)
	{
		Disk disk(m_current_path);
		disk.create_subfolder(new_folder);
		return;
	}
	//���� �������������� � ����� �����-��
	if (m_is_in_folder)
	{
		Folder folder(m_current_path);
		folder.create_subfolder(new_folder);
		return;
	}
}

void Computer::create_file_processing(std::string second_token)
{
	std::string new_file;
	//�������� ������ ����+��� ��� ���
	if (is_the_path_is_full(second_token))
	{//����+���
		new_file =second_token;
	}
	else
	{//���
		new_file = m_current_path + second_token;
	}
	//���� �������������� � ����������
	if (m_current_path == "computer")
	{
		throw fm_exception("� ������ ����� ���������� ������� ����� ����");
		return;
	}
	//���� �������������� � ����� �����
	if (m_current_path.size() == 3)
	{
		Disk disk(m_current_path);
		disk.create_file(new_file);
		return;
	}
	//���� �������������� � ����� �����-��
	if (m_is_in_folder)
	{
		Folder folder(m_current_path);
		folder.create_file(new_file);
		return;
	}
}

void Computer::delete_sub_function(std::string path)
{
	const char* char_str = path.c_str();
	const char* char_str1 = m_list_of_disks[0].c_str();
	//�������� ���� �� ������ �� ���� path
	if (is_object_exist(path))
	{
		//�������� ������ ���� ��� �����
		if (is_the_folder_at_path(path))
			//���� �� ������ ��������� �����
		{
			//������ ������� ��������� ��������� ������ ������� ����������\�����
			if (_chdir(char_str1) == 0)
			{
				//������ �����
				if (_rmdir(char_str) == 0)
				{
					std::cout << "����� \"" << path << "\" �������" << std::endl;
					return;
				}
				std::cout << "������ �������� �����(�������� ��� �� ������)" << std::endl;
				return;
			}
			std::cout << "������ �������� �����" << std::endl;
			return;
		}
		//���� �� ������ ����
		//������ ����
		if (remove(char_str) == 0)
			std::cout << "���� \"" << path << "\" ������" << std::endl;
		else
			std::cout << "������ �������� �����" << std::endl;
		return;
	}
	//������ �� ������
	std::cout << "������ ��������: ����(��� �����) �� ������" << std::endl;
}

bool Computer::rename_file_or_folde(std::string parameters)
{
	std::string old_name;
	std::string new_name;
	//���������� ��������� �� ������ �����(��������� ��������) � ������ �����(����� ��������)
	parameters_to_tokens(parameters, old_name, new_name);
	//���� �� ������� ����� ��������
	if (new_name == "")
	{
		std::cout << "������ ��������������\\�����������: �� ������� ����� ��������" << std::endl;
		return 0;
	}
	//�������� ������� �� �������� ��� � ������ ����� ��� ������ �������� �����
	if (!is_the_path_is_full(old_name))//���� ������ ��� �������	
	{
		//�������� ���� �� ������ � ������� �������� 
		if (is_object_exist(m_current_path + old_name))
		{
			//�������� ������� �� ����� ��� � ������ ����� ��� ������ �������� �����
			if (!is_the_path_is_full(new_name))//������ ���
			{//�������������� ������ � ������� �����(���/���)
				old_name = m_current_path + old_name;
				new_name = m_current_path + new_name;
				const char* char_old_name = old_name.c_str();
				const char* char_new_name = new_name.c_str();
				if (rename(char_old_name, char_new_name) != 0)
				{
					std::cout << "������: ��������������/����������� �� ��������� (���/���) " << std::endl;
					return 0;
				}
				return 1;

			}
			else//������� ���+����
			{//��������������/��������� ������ (���/����+���)
				old_name = m_current_path + old_name;
				const char* char_old_name = old_name.c_str();
				const char* char_new_name = new_name.c_str();
				if (rename(char_old_name, char_new_name) != 0)
				{
					std::cout << "������: ��������������/����������� �� ��������� (���/����+���)" << std::endl;
					return 0;
				}
				return 1;
			}
		}
	}
	else//������� ���+���� �������
	{
		//�������� ���� �� ������ �� ���� path
		if (is_object_exist(old_name))
		{
			//�������� ������� �� ����� ��� � ������ ����� ��� ������ �������� �����
			if (!is_the_path_is_full(new_name))//������ ���
			{//�������������� ������(���+����/���)
				//������� ���� �� new_name;
				std::string path_new_name = old_name;
				while (path_new_name.size() != 0)
				{
					if (path_new_name[path_new_name.size() - 1] != '\\')
					{
						path_new_name.pop_back();
					}
					else
						break;
				}
				new_name = path_new_name + new_name;
				const char* char_old_name = old_name.c_str();
				const char* char_new_name = new_name.c_str();
				if (rename(char_old_name, char_new_name) != 0)
				{
					std::cout << "������: ��������������/����������� �� ��������� (���+����/���)" << std::endl;
					return 0;
				}
				return 1;
			}
			else//������� ���+����
			{//��������������/��������� ������ (���+����/����+���)
				const char* char_old_name = old_name.c_str();
				const char* char_new_name = new_name.c_str();
				if (rename(char_old_name, char_new_name) != 0)
				{
					std::cout << "������: ��������������/����������� �� ��������� (���+����/����+���)" << std::endl;
					return 0;
				}
				return 1;
			}
		}
	}
	//������ �� ������
	std::cout << "������ ��������������\\�����������: ��������� ����(��� �����) �� ������" << std::endl;
	return 0;
}

void Computer::copy_file(std::string parameters)
{
	std::string old_name;
	std::string new_name;
	//���������� ��������� �� ������ �����(��������� ��������) � ������ �����(����� ��������)
	parameters_to_tokens(parameters, old_name, new_name);
	//�������� �� ������ �� ���������
	if (old_name == "" || new_name == "")
	{
		std::cout << "������: �� ��� ��������� �������" << std::endl;
		return;
	}
	// //�������� ������ �� ���������� ������ � ������ ����� ��� ������ �������� 
	if (!is_the_path_is_full(old_name))
		//���� ������ ��� �������
	{//�������� � ����� ������� ���� ������� �����
		old_name = m_current_path + old_name;
	}
	//�������� ���� �� ������ �� ������� ���� 
	if (!is_object_exist(old_name))
	{//������� ���
		std::cout << "����/����� '" << old_name << "' �� ����������" << std::endl;
		return;
	}
	//�������� ������ �� ���� ����������, ��� �������� ����������� � ������� ����� � ����� ������ �����
	if (is_the_path_is_full(new_name))
	{//���� ����, �������� � new_name � ���� ��� ����������� �������
		std::string name = get_object_name(old_name);
		if (new_name[new_name.size() - 1] != '\\')
			new_name += '\\';
		new_name = new_name + name;
	}
	else
	{//���� ���, �������� � new_name ���� ����������� �������+����� ���
		std::cout << "�����: �� ������ ���� ���� �����������" << std::endl;
		return;
	}
	const char* char_old_name = old_name.c_str();
	const char* char_new_name = new_name.c_str();
	size_t size_old = strlen(char_old_name) + 1;
	size_t size_new = strlen(char_new_name) + 1;
	wchar_t* w_old_name;
	wchar_t* w_new_name;
	try {
		w_old_name = new wchar_t[size_old];
	}
	catch (std::exception ex)
	{
		std::cout << "������ ��� ��������� ������" << std::endl;
		return;
	}
	try {
		w_new_name = new wchar_t[size_new];
	}
	catch (std::exception ex)
	{
		std::cout << "������ ��� ��������� ������" << std::endl;
		return;
	}
	size_t converted_chars = 0;
	mbstowcs_s(&converted_chars, w_old_name, size_old, char_old_name, _TRUNCATE);
	converted_chars = 0;
	mbstowcs_s(&converted_chars, w_new_name, size_new, char_new_name, _TRUNCATE);
	//�������� ������ ����� ��� ����
	if (!is_the_folder_at_path(old_name))
	{//���� ������ ���� ������� ���
		if (CopyFile(w_old_name, w_new_name, true) == 0)
			std::cout << "copy is bad" << std::endl;
		delete[]w_new_name;
		delete[]w_old_name;
		return;

	}
	else
	{//���� ������ �����
		//�������� ���������� �� ����� �� ������ ����
		std::string path1 = old_name+"\\";
		std::string path2 = get_object_path(new_name);
		while (path2.size() > path1.size())
		{
			path2.pop_back();
			path2 = get_object_path(path2);
		}
		std::string buf_new_name;//��������� ���������� ����
		std::string temp_s = "C:\\19amzh273f83jpe3243idhvle\\";//���� ��� ��������� �����
		if (path1 == path2)
		{//����� ���������� �� ������ �������� �����, ������ ������� ������� � ������ �����
			//� ����� ������� ���� ���� ����� �����������
			buf_new_name = new_name;
			//� new_name ��������� ���� ��������� �����
			new_name = "C:\\19amzh273f83jpe3243idhvle\\" + get_object_name(new_name);
			delete[]w_new_name;
			const char* char_new_name_buf = new_name.c_str();
			size_new = strlen(char_new_name_buf) + 1;
			try {
				w_new_name = new wchar_t[size_new];
			}
			catch (std::exception ex)
			{
				std::cout << "������ ��� ��������� ������" << std::endl;
				return;
			}
			converted_chars = 0;
			mbstowcs_s(&converted_chars, w_new_name, size_new, char_new_name_buf, _TRUNCATE);
			//������ ��������� �����
			const char* char_name = temp_s.c_str();
			if (_mkdir(char_name) == -1)
			{
				std::cout << "������ ��� �������� ��������� ����� \"" << temp_s << "\"" << std::endl;
				return;
			}
			
		}
		//������� �����
		try {
			std::filesystem::copy(w_old_name, w_new_name, std::filesystem::copy_options::recursive);
		}
		catch (std::filesystem::filesystem_error ex)
		{
			std::cout << "������: " << ex.what() << std::endl;
			return;
		}
		//���� ����� ����������� �� �� ������ - �������� ������������� � ������ �����
		if (buf_new_name != "")
		{
			if (!rename_file_or_folde(new_name + "/" + buf_new_name))
			{
				std::cout << "������ ����������� ����� �����������" << std::endl;
			}
			//������ ��������� �����
			const char* char_str = temp_s.c_str();
			_rmdir(char_str);
			
		}
	}
	delete[]w_new_name;
	delete[]w_old_name;
	return;
}




