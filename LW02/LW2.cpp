#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

size_t FindPos(unsigned char simbol, std::vector<unsigned char> vecot)
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

int main()
{
	std::vector<unsigned char> alphabet;
	for (size_t i = 0; i < 256; i++)
	{
		alphabet.push_back(static_cast<unsigned char>(i));
	}

	std::ifstream iFile("./input", std::ios::binary);
	std::ofstream oFile("./output", std::ios::binary);

	std::string key;
	std::cout << "Key: ";
	std::getline(std::cin, key);
	size_t lenKey = key.size();
	std::cout << "Key length: " << lenKey << std::endl;

	std::vector<std::vector<unsigned char>> tableViginera;
	tableViginera.resize(lenKey);
	for (size_t i = 0; i < tableViginera.size(); i++)
	{
		tableViginera[i].resize(alphabet.size());
	}

	for (size_t i = 0; i < lenKey; i++)
	{
		int j = key[i];
		std::copy(alphabet.begin() + j, alphabet.end(), tableViginera[i].begin());
		std::copy(alphabet.begin(), alphabet.begin() + j, tableViginera[i].end() - j);
	}

	std::string buff;

	char x;
	unsigned char y, z;
	unsigned int i = -1;
	while (iFile.read((char*)&x, sizeof(x)))
	{
		y = static_cast<unsigned char>(x);
		z = tableViginera[(i == lenKey - 1) ? i = 0 : ++i][y];
		oFile.write((char*)&z, sizeof(z));
	}

	iFile.close();
	oFile.close();

	iFile.open("./output", std::ios::binary);
	oFile.open("./output2", std::ios::binary);
	i = -1;
	while (iFile.read((char*)&x, sizeof(x)))
	{
		y = static_cast<unsigned char>(x);
		z = alphabet[FindPos(y, tableViginera[(i == lenKey - 1) ? i = 0 : ++i])];
		oFile.write((char*)&z, sizeof(z));
	}
	return EXIT_SUCCESS;
}