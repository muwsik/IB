//#include <iostream>
//#include <cmath>
//
//int main()
//{
//	int number;
//	std::cout << "Edit number: ";
//	std::cin >> number;
//
//	while (number < 1 || number > INT_MAX)
//	{
//		std::cout << "Error! Edit number: ";
//		std::cin >> number;
//	}
//
//	int i = 2;
//	while (i <= number)
//	{
//		if (number%i == 0)
//		{
//			std::cout << i;
//			number /= i;
//			if (number > 1)
//				std::cout << " * ";
//		}
//		else
//			i++;
//	}
//	std::cout << std::endl;
//	return EXIT_SUCCESS;
//}