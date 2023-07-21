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
	//основная функция
	void Start();
	//обработка команды help вывод описания помощи на экран
	void help();
	//обработка введенной команды
	bool processing_choise(std::string choice, Computer& comp);
	//разлаживаю строку введенной команды на 2 токена - команда и параметр команды
	void string_to_tokens(std::vector<std::string>& tokens, std::string& choice);
	//обработка токенов - если есть совпадение с командой возврат индекса команды
	//если нет совпадения возврат 1(если 1 то заново запрашивается ввод команды)
	int processing_the_tokens(std::vector<std::string>& tokens);
	//запускает команду согласно совпавшему токену
	void processing_command(int& rezult, std::string second_token, std::string& choice, Computer& comp);
};

