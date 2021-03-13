#include <iostream>
#include <cmath>

int main()
{
	int a, b;
	std::cout << "Edit first number: ";
	std::cin >> a;

	std::cout << "Edit second number: ";
	std::cin >> b;

	
	int U[3] = { a, 1, 0 }, V[3] = { b, 0, 1 }, T[3];
	int q;
	do
	{
		q = U[0] / V[0];
		T[0] = U[0] % V[0];
		T[1] = U[1] - q*V[1];
		T[2] = U[2] - q*V[2];
		for (int i = 0; i < 3; i++)
		{
			U[i] = V[i];
			V[i] = T[i];
		}
	} while (V[0] != 0);
	//std::cout << "NOD is " << U[0] << "; x =" << U[1] << "; y =" << U[2] << std::endl;
	std::cout << a << "*" << U[1] << "+" << b << "*" << U[2] << "=" << U[0] << std::endl;

	return EXIT_SUCCESS;
}