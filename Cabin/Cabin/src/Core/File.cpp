#include "Core/File.h"
#include <iostream>
#include <fstream>
#include <sstream>

String File::ReadFile(const char* filePath)
{
	std::stringstream fileContents;

	std::ifstream file(filePath);

	if (file.is_open())
	{
		while (!file.eof() && file.peek() != EOF)
		{
			std::string newLine;
			std::getline(file, newLine);
			fileContents << newLine << std::endl;
		}

		if (file.fail())
		{
			std::cout << "Failed to read file: \"" << filePath << "\"" << std::endl;
			return "";
		}
	}
	else
	{
		std::cout << "Failed to open file: \"" << filePath << "\"" << std::endl;
		return "";
	}

	file.close();
	return String(fileContents.str().c_str());
}

bool File::WriteFile(const char* filePath, const char* fileContents)
{
	std::ofstream file;
	file.open(filePath, std::ios::out);

	if (file.is_open())
	{
		file.clear();
		file << fileContents;
		file.flush();
		if (file.fail())
		{
			std::cout << "Failed to write to file: \"" << filePath << "\"" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "Failed to open file: \"" << filePath << "\"" << std::endl;
		return false;
	}
	file.close();

	return true;
}

template<typename T>
T File::ReadFileAsClass(const char* filePath)
{
	T output;

	std::ifstream file(filePath, std::ios::in);
	if (file.open())
	{
		file.seekg(0);
		file.read((char*)output, sizeof(output));
		if (file.fail())
		{
			std::cout << "Failed to read file: \"" << filePath << "\"" << std::endl;
			return nullptr;
		}
	}
	file.close();

	return output;
}

template<typename T>
bool File::WriteClassAsFile(const char* filePath, const T& fileContents)
{
	std::ofstream file(filePath, std::ios::app);
	if (file.open())
	{
		file.write((char*)fileContents, sizeof(fileContents));
		file.flush();
		if (file.fail())
		{
			std::cout << "Failed to write to file: \"" << filePath << "\"" << std::endl;
			return false;
		}
	}
	file.close;

	return true;
}
