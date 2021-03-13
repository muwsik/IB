//#include <iostream>
//#include <string>
//#include <fstream>
//
//void main()
//{
//	std::string key;
//	std::cout << "Key: ";
//	std::cin >> key;
//	size_t lenKey = key.size();
//	std::cout << "Key length: " << lenKey << std::endl;
//	std::ifstream fileInput("./output.txt", std::ios::binary);
//	std::ofstream fileOutput("./result.txt", std::ios::binary);
//	char x, z;
//	for (size_t i = 0; i < lenKey; i++)
//	{
//		fileInput.read((char*)&x, sizeof(x));
//		z = x ^ key[i];
//		fileOutput.write((char*)&z, sizeof(z));
//	}
//	fileInput.close();
//	fileOutput.close();
//}