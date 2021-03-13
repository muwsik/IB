//#include <iostream>
//#include <string>
//
//std::string Coding(std::string str, std::string key);
//
//void main()
//{
//	std::string inputString, key;
//	std::cout << "inputString: ";
//	std::getline(std::cin, inputString);
//	size_t lengthString = inputString.size();
//	std::cout << "Length inputString: " << lengthString << std::endl << "Key: ";
//	std::cin >> key;
//	size_t lengthKey = key.size();
//	std::string codedString = Coding(inputString, key);
//	std::cout << "Result coding: " << codedString << std::endl;
//	std::cout << "Result decoding: " << Coding(codedString, key) << std::endl;
//}
//
//std::string Coding(std::string str, std::string key)
//{
//	int x, y, z, j = -1;
//	std::string result;
//	for (size_t i = 0; i < str.size(); ++i)
//	{
//		x = static_cast<int>(str[i]);
//		y = static_cast<int>(key[(j == key.size() - 1) ? j = 0 : ++j]);
//		z = x ^ y;
//		result += static_cast<char>(z);
//	}
//	return result;
//}
