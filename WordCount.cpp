#include <iostream>
#include <vector>
#include <fstream>

std::vector<std::string> filenames;
std::vector<char> commands;

void CommandsParser(std::string str)
{
	//'l' is #lines
	//'c' is #bytes
	//'w' is #words
	//'m' is #char
	if (str[1] == '-')
	{
		if (str[2] == 'l')
		{
			commands.push_back('l');
		}
		else if (str[2] == 'b')
		{
			commands.push_back('c');
		}
		else if (str[2] == 'w')
		{
			commands.push_back('w');
		}
		else
		{
			commands.push_back('m');
		}
		return;
	}
	for (int i = 1; i < str.size(); i++)
	{
		commands.push_back(str[i]);
	}
}

void Check(std::string str)
{
	if (str[0] == '-')
	{
		CommandsParser(str);
	}
	else
	{
		filenames.push_back(str);
	}
}

long long CountLines(std::string file)
{
	std::ifstream fin;
	fin.open(file);
	
	std::string str;
	long long lines = 0;
	
	while (getline(fin, str))
	{
		lines++;
	}
	
	fin.close();
	
	return lines;
}

long long CountBytes(std::string file)
{
	std::ifstream fin;
	fin.open(file);
	
	fin.seekg(0, std::ios_base::end);
	long long bytes = (long long)(fin.tellg());
	
	fin.close();
	
	return bytes;
}

long long CountWords(std::string file)
{
	std::ifstream fin;
	fin.open(file);
	
	std::string word;
	long long words = 0;
	
	while (fin >> word)
	{
		words++;
	}
	
	fin.close();
	
	return words;
}

long long CountChars(std::string file)
{
	std::ifstream fin;
	fin.open(file);
	
	std::string word;
	long long chars = 0;
	int code;
	
	while (fin >> word)
	{
		for (int i = 0; i < word.size(); i++)
		{
			code = (int)(word[i]);
			if ((code >= 65 && code <= 90) || (code >= 97 && code <= 122))
			{
				chars++;
			}
		}
	}
	
	fin.close();
	
	return chars;
}

int main(int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		Check(argv[i]);
	}
	
	std::string cur_file;
	long long lines, bytes, words, chars;
	char cur_command;
	
	for (int i = 0; i < filenames.size(); i++)
	{
		cur_file = filenames[i];
		
		if (commands.size() == 0)
		{
			std::cout << CountLines(cur_file) << ' ' << CountWords(cur_file) << ' ' << CountBytes(cur_file) << ' ' << CountChars(cur_file) << ' ';
		}
		
		for (int j = 0; j < commands.size(); j++)
		{
			cur_command = commands[j];
			if (cur_command == 'l')
			{
				std::cout << CountLines(cur_file) << ' ';
			}
			else if (cur_command == 'c')
			{
				std::cout << CountBytes(cur_file) << ' ';
			}
			else if (cur_command == 'w')
			{
				std::cout << CountWords(cur_file) << ' ';
			}
			else
			{
				std::cout << CountChars(cur_file) << ' ';
			}
		}
		
		std::cout << cur_file << std::endl;
	}
}
