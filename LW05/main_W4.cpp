//#include <iostream>
//#include <cmath>
//
//int main()
//{
//	int number1;
//	std::cout << "Edit first number: ";
//	std::cin >> number1;
//	while (number1 < 1 || number1 > INT_MAX)
//	{
//		std::cout << "Error! Edit number: ";
//		std::cin >> number1;
//	}
//
//	int number2;
//	std::cout << "Edit second number: ";
//	std::cin >> number2;
//	while (number2 < 1 || number2 > INT_MAX)
//	{
//		std::cout << "Error! Edit number: ";
//		std::cin >> number2;
//	}
//
//	int x;
//	do
//	{
//		x = number1 % number2;
//		number1 = number2;
//		number2 = x;
//	} while (number2 != 0);
//	std::cout << "NOD is " << number1 << std::endl;
//
//	return EXIT_SUCCESS;
//}