#include <iostream>
#include <string>
#include <fstream>

void main()
{
	std::string key;
	std::cout << "Key: ";
	std::cin >> key;
	size_t lenKey = key.size() - 1;
	std::cout << "Key length: " << lenKey + 1 << std::endl;


	std::ifstream fileInput("./output", std::ios::binary);
	std::ofstream fileOutput("./input2", std::ios::binary);

	char x, y, z;
	unsigned int i = -1;
	while (fileInput.read((char*)&x, sizeof(x)))
	{
		y = static_cast<int>(key[(i == lenKey) ? i = 0 : ++i]);
		z = x ^ y;
		fileOutput.write((char*)&z, sizeof(z));
	}

	fileInput.close();
	fileOutput.close();
}