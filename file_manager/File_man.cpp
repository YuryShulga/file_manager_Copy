#include "File_man.h"

File_man::File_man()
{
}

void File_man::Start()
{
	using namespace std;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Computer comp;
	cout << "\t�������� ��������" << endl;
	cout << "��� ������ ������� \"help\"" << endl;
	string choice;
	bool run = true;
	while (run) {
		//����� �� ����� ������� ��������������
		cout << comp.get_current_path() << ">";
		//������ ����� ������� �� ������������
		getline(cin, choice);
		//��������� ��������� �������
		try {
			run = processing_choise(choice, comp);
		}
		catch (fm_exception ex)
		{
			cout << "������: " << ex.what() << endl;
		}
	}
	cout << "...Goodbye..." << endl;
}

void File_man::help()
{
	std::cout << "-----------------------HELP-----------------------------------" << std::endl;
	std::cout << "1.�������� ���������� �����(�����, ����������, �����) \"dir\"" << std::endl;
	std::cout << "2.������� ����� \"new_dir '�������� ����� �����'\"" << std::endl;
	std::cout << "3.������� ���� \"new_file '�������� ������ �����'\"" << std::endl;
	std::cout << "4.����������� ����/����� \"copy '�������� �����(����+��������)'/'���� (���� �����������)'\"" << std::endl;
	std::cout << "5.������������� ����/����� \"rename '�������� �����(����+��������)'/'����� �������� �����(����+����� ��������)'\"" << std::endl;
	std::cout << "6.������� ����� ��� ���� \"del '�������� ����� ��� �����'\"" << std::endl;
	std::cout << "7.������� � �����(���� ����) \"cd '�����(���� ����)'\"" << std::endl;
	std::cout << "8.������� �� ������� ����(����� �� �����) \"cd..\"" << std::endl;
	std::cout << "9.��� ������ ������� \"help\"" << std::endl;
	std::cout << "10.��� ������ �� ��������� ������� \"exit\"" << std::endl;
	std::cout << "----------------------HELP END--------------------------------" << std::endl;
}

bool File_man::processing_choise(std::string choice, Computer& comp)
{
	//� ���� ������ ����� �������� ������ �������
	std::vector<std::string> tokens;
	tokens.push_back("");
	tokens.push_back("");
	//���������� ������ ��������� ������� �� 2 ������ - ������� � �������� �������
	string_to_tokens(tokens, choice);
	//���� ��������� ��������� ���������� ������ ��������� ���� �����
	bool continue_or_exit;
	int rezult;
	//��������� �������
	rezult = processing_the_tokens(tokens);
	continue_or_exit = rezult;
	//���� ����� ������ ����������� - ������ ������� ��������� �������������
	//0 - ������� exit
	//1 - ������� �� �������
	if (rezult > 0)
		processing_command(rezult, tokens[1], choice, comp);
	return continue_or_exit;
}

void File_man::string_to_tokens(std::vector<std::string>& tokens, std::string& choice)
{
	bool first_token = true;
	bool second_token_start = false;
	for (int i = 0; i < choice.size(); i++)
	{
		//������� ������ �����
		if (first_token && choice[i] != ' ')
		{
			tokens[0] += choice[i];
		}
		//������� ������ ����� ���� �� ����
		else
		{
			first_token = false;
			if (second_token_start)
				tokens[1] += choice[i];
			if (choice[i] != ' ' && !second_token_start)
			{
				second_token_start = true;
				tokens[1] += choice[i];
			}
		}
	}
}

int File_man::processing_the_tokens(std::vector<std::string>& tokens)
{
	//������� dir
	if (tokens[0] == "dir")
		return 2;
	//������� ������
	if (tokens[0] == "help" && tokens[1] == "")
		return 3;
	//������� ����� �� ���������
	if (tokens[0] == "exit" && tokens[1] == "")
		return  0;
	//������� cd "�����-�� ���� " - ������� �� ����
	if (tokens[0] == "cd" && tokens[1] != "" && tokens[1] != "..")
		return 4;
	//������� cd.. ����� �� �����(�� ������� ����)
	if (tokens[0] == "cd.." && tokens[1] == "")
		return 5;
	//������� mkdir ������� �����
	if (tokens[0] == "new_dir" && tokens[1] != "")
		return 6;
	//������� ������� ����
	if (tokens[0] == "new_file" && tokens[1] != "")
		return 7;
	//������� ������� ����� ��� ����
	if (tokens[0] == "del" && tokens[1] != "")
		return 8;
	//������� �������������/����������� ����� ��� ����
	if (tokens[0] == "rename" && tokens[1] != "")
		return 9;
	//������� ���������� �����/����
	if (tokens[0] == "copy" && tokens[1] != "")
		return 10;
	return 1;
}

void File_man::processing_command(int& rezult, std::string second_token, std::string& choice, Computer& comp)
{
	switch (rezult)
	{
	case 1://������� �� ����������(������� ������� ����������� ���� ���� ������)
	{
		std::cout << "��������� ������� \"" << choice << "\" " << " �����������" << std::endl;
		break;
	}
	case 2://������� dir
	{
		comp.do_dir();
		break;
	}
	case 3://������� help
	{
		help();
		break;
	}
	case 4://������� cd "�����-�� ����� "
	{
		comp.cd_path(second_token);
		break;
	}
	case 5://������� cd.. ����� �� �����(�� ������� ����)
	{
		comp.cd_out();
		break;
	}
	case 6://������� create_dir ������� �����
	{
		comp.create_dir(second_token);
		break;
	}
	case 7://������� create_file ������� ����
	{
		comp.create_file_processing(second_token);
		break;
	}
	case 8://������� ������� �����
	{
		comp.delete_folder_or_file(second_token);
		break;
	}
	case 9://������� �������������/����������� ����� ��� ����
	{
		comp.rename_file_or_folde(second_token);
		break;
	}
	case 10://������� ���������� �����/����
	{
		comp.copy_file(second_token);
		break;
	}
	default:
		break;
	}
}
