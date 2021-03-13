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
//	int count = 0;
//	int min = number1 > number2 ? number2 : number1;
//	for (int i = 2; i <= min; i++)
//	{
//		if ((number1%i == 0) && (number2%i == 0))
//		{
//			count++;
//		}
//	}
//
//	if (count <= 2)
//		std::cout << "Yes!" << std::endl;
//	else
//		std::cout << "No!" << std::endl;
//
//	return EXIT_SUCCESS;
//}