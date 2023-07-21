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
	cout << "\tФайловый менеджер" << endl;
	cout << "для помощи введите \"help\"" << endl;
	string choice;
	bool run = true;
	while (run) {
		//вывод на экран текущее местоположение
		cout << comp.get_current_path() << ">";
		//запрос ввода команды от пользователя
		getline(cin, choice);
		//обработка введенной команды
		try {
			run = processing_choise(choice, comp);
		}
		catch (fm_exception ex)
		{
			cout << "ошибка: " << ex.what() << endl;
		}
	}
	cout << "...Goodbye..." << endl;
}

void File_man::help()
{
	std::cout << "-----------------------HELP-----------------------------------" << std::endl;
	std::cout << "1.показать содержимое папки(диска, компьютера, файла) \"dir\"" << std::endl;
	std::cout << "2.создать папку \"new_dir 'название новой папки'\"" << std::endl;
	std::cout << "3.создать файл \"new_file 'название нового файла'\"" << std::endl;
	std::cout << "4.скопировать файл/папку \"copy 'название файла(путь+название)'/'путь (куда скопировать)'\"" << std::endl;
	std::cout << "5.переименовать файл/папку \"rename 'название файла(путь+название)'/'новое название файла(путь+новое название)'\"" << std::endl;
	std::cout << "6.удалить папку или файл \"del 'название папки или файла'\"" << std::endl;
	std::cout << "7.переход в папку(либо путь) \"cd 'папка(либо путь)'\"" << std::endl;
	std::cout << "8.переход на уровынь выше(выход из папки) \"cd..\"" << std::endl;
	std::cout << "9.для помощи введите \"help\"" << std::endl;
	std::cout << "10.для выхода из программы введите \"exit\"" << std::endl;
	std::cout << "----------------------HELP END--------------------------------" << std::endl;
}

bool File_man::processing_choise(std::string choice, Computer& comp)
{
	//в этот массив будут записаны токены команды
	std::vector<std::string> tokens;
	tokens.push_back("");
	tokens.push_back("");
	//разлаживаю строку введенной команды на 2 токена - команда и параметр команды
	string_to_tokens(tokens, choice);
	//сюда запишется результат продолжать работу программы либо выход
	bool continue_or_exit;
	int rezult;
	//обработка токенов
	rezult = processing_the_tokens(tokens);
	continue_or_exit = rezult;
	//если токен удачно расшифрован - запуск команды введенной пользователем
	//0 - команда exit
	//1 - команда не найдена
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
		//отделяю первый токен
		if (first_token && choice[i] != ' ')
		{
			tokens[0] += choice[i];
		}
		//отделяю второй токен если он есть
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
	//команда dir
	if (tokens[0] == "dir")
		return 2;
	//команда помощь
	if (tokens[0] == "help" && tokens[1] == "")
		return 3;
	//команда выход из программы
	if (tokens[0] == "exit" && tokens[1] == "")
		return  0;
	//команда cd "какой-то путь " - перейти по пути
	if (tokens[0] == "cd" && tokens[1] != "" && tokens[1] != "..")
		return 4;
	//команда cd.. выход из папки(на уровень выше)
	if (tokens[0] == "cd.." && tokens[1] == "")
		return 5;
	//команда mkdir создать папку
	if (tokens[0] == "new_dir" && tokens[1] != "")
		return 6;
	//команда создать файл
	if (tokens[0] == "new_file" && tokens[1] != "")
		return 7;
	//команда удалить папку или файл
	if (tokens[0] == "del" && tokens[1] != "")
		return 8;
	//команда переименовать/переместить папку или файл
	if (tokens[0] == "rename" && tokens[1] != "")
		return 9;
	//команда копировать папку/файл
	if (tokens[0] == "copy" && tokens[1] != "")
		return 10;
	return 1;
}

void File_man::processing_command(int& rezult, std::string second_token, std::string& choice, Computer& comp)
{
	switch (rezult)
	{
	case 1://команда не определена(команда введена неправильно либо ввод мусора)
	{
		std::cout << "введенная команда \"" << choice << "\" " << " некорректна" << std::endl;
		break;
	}
	case 2://команда dir
	{
		comp.do_dir();
		break;
	}
	case 3://команда help
	{
		help();
		break;
	}
	case 4://команда cd "какая-то папка "
	{
		comp.cd_path(second_token);
		break;
	}
	case 5://команда cd.. выход из папки(на уровень выше)
	{
		comp.cd_out();
		break;
	}
	case 6://команда create_dir создать папку
	{
		comp.create_dir(second_token);
		break;
	}
	case 7://команда create_file создать файл
	{
		comp.create_file_processing(second_token);
		break;
	}
	case 8://команда удалить папку
	{
		comp.delete_folder_or_file(second_token);
		break;
	}
	case 9://команда переименовать/переместить папку или файл
	{
		comp.rename_file_or_folde(second_token);
		break;
	}
	case 10://команда копировать папку/файл
	{
		comp.copy_file(second_token);
		break;
	}
	default:
		break;
	}
}
