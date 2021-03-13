#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

class TableViginera
{
public:		static std::vector<unsigned char> alphabet;
public:		std::vector<std::vector<unsigned char>> tableViginera;
private:	std::string tKey;
private:	static void AssignAlphabet(size_t size);
public:		size_t FindPos(unsigned char simbol, std::vector<unsigned char> vecot);
public:		std::string Coding(std::string string);
public:		std::string Decoding(std::string string);
public:		TableViginera(std::string key);
public:		~TableViginera();
};