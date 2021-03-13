#include "TableViginera.h"

std::vector<unsigned char> TableViginera::alphabet{};


void TableViginera::AssignAlphabet(size_t size)
{
	alphabet.clear();
	for (size_t i = 0; i < size; i++)
	{
		alphabet.push_back(static_cast<unsigned char>(i));
	}
}

size_t TableViginera::FindPos(unsigned char simbol, std::vector<unsigned char> vecot)
{
	for (size_t i = 0; i < vecot.size(); i++)
	{
		if (simbol == vecot[i])
		{
			return i;
		}
	}
	abort();
}

std::string TableViginera::Coding(std::string string)
{
	int j = -1;
	std::string result;
	for (size_t i = 0; i < string.size(); i++)
	{
		result += tableViginera[j == tKey.size() - 1 ? j = 0 : ++j][FindPos(string[i], alphabet)];
	}
	return result;
}

std::string TableViginera::Decoding(std::string string)
{
	int j = -1;
	std::string result;
	for (size_t i = 0; i < string.size(); i++)
	{
		result += alphabet[FindPos(string[i], tableViginera[j == tKey.size() - 1 ? j = 0 : ++j])];
	}
	return result;
}

TableViginera::TableViginera(std::string key) : tKey(key)
{
	TableViginera::AssignAlphabet(256);
	size_t lenKey = tKey.size();

	tableViginera.resize(lenKey);
	for (size_t i = 0; i < tableViginera.size(); i++)
	{
		tableViginera[i].resize(alphabet.size());
	}

	for (size_t i = 0; i < lenKey; i++)
	{
		int j = FindPos(key[i], alphabet);
		std::copy(alphabet.begin() + j, alphabet.end(), tableViginera[i].begin());
		std::copy(alphabet.begin(), alphabet.begin() + j, tableViginera[i].end() - j);
	}
}

TableViginera::~TableViginera()
{	}
