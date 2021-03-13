#include "numbers.h"
#include <iostream>
#include <fstream>
#include <string>

#define BYTES_COUNT 2

bool CountBlocks(const std::string& name, size_t &count)
{
	std::ifstream iFile(name, std::ios::binary | std::ios::ate);

	count = static_cast<size_t>(iFile.tellg()) / BYTES_COUNT;

	return static_cast<bool>(count * 2 - static_cast<size_t>(iFile.tellg()));
}

int64_t H(const std::string& name)
{
	std::ifstream iFile(name, std::ios::binary);
	size_t count; uint64_t result = 0;

	char *coupleByte = new char[2];

	if (!CountBlocks(name, count))
	{
		for (size_t i = 0; i < count; ++i)
		{
			iFile.read((char *)coupleByte, sizeof(char)*BYTES_COUNT);
			result += *(int16_t*)coupleByte;
		}
		delete[] coupleByte;
		return result % 0xffff; //2^16
	}
	else
	{
		for (size_t i = 0; i < count; ++i)
		{
			iFile.read((char *)coupleByte, sizeof(char)*BYTES_COUNT);
			result += *(int16_t*)coupleByte;
		}
		iFile.read(reinterpret_cast<char *>(coupleByte), sizeof(char));
		result += *coupleByte;
		delete[] coupleByte;
		return result % 0xffff;
	}
}

uint32_t Generation(int32_t p)
{
	for (int k = random(10, p / 10); k < p; k++)
	{
		if (Prime(k, p))
		{
			return k;
		}
	}
	return 0;
}

uint32_t g = 45659;
uint32_t p = 46817;

int main(void)
{
	std::string name;
	std::cout << "File: ";
	std::getline(std::cin, name);

	char Q; std::cout << "Signature? (y/n) \n> ";
	std::cin >> Q;

	if (Q == 'y')
	{
		uint32_t x = random(2, p);
		uint32_t y = modulePow(g, x, p);
		std::cout << "Open key ( " << p << " " << g << " " << y << " )" << std::endl;

		uint32_t k = Generation(p - 1);
		uint32_t r = modulePow(g, k, p);
		vector_t V = evklidSolve(k, p - 1);
		int64_t s = ((H(name) - x * r) % (p - 1) * V.x) % (p - 1);
		if (s < 0)
			s += p - 1;
		std::cout << "Signed message < " << H(name) << " " << r << " " << s << " >" << std::endl;
	}
	else if (Q == 'n')
	{
		uint32_t y, r, s;
		std::cout << "Enter open key and signature: ";
		std::cin >> y >> r >> s;
		if ((modulePow(y, r, p)*modulePow(r, s, p) % p) == modulePow(g, H(name), p))
		{
			std::cout << "Original message!" << std::endl;
		}
		else std::cout << "Not the original message!" << std::endl;
		std::cout << H(name);
	}
	else abort();

	return EXIT_SUCCESS;
}