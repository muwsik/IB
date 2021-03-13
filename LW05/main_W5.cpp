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
//	for (size_t i = 1; i <= number1*number2; i++)
//	{
//		if ((i%number1 == 0) && (i%number2 == 0))
//		{
//			x = i;
//			break;
//		}
//	}
//	std::cout << "NOK is " << x << std::endl;
//	return EXIT_SUCCESS;
//}