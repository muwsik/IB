#include <iostream>
#include <fstream>
#include <vector>
#include "RSA.h"

int main()
{
	RSA A(1);

	A.inf();
	RSA::publicKey keyB;

	char Q;
	std::cout << "Encode? (y/n)\n> ";	std::cin >> Q;

	if (Q == 'y')
	{
		std::cout << "Enter public key of accomplice: ";
		std::cin >> keyB.N >> keyB.d;
		std::string iFile = "./input.txt";
		std::string oFile = "./coded.txt";
		writeAllBytes<int64_t>(A.encrypt(readAllBytes<int8_t>(iFile), keyB), oFile);
	}
	else if (Q == 'n')
	{
		std::string iFile = "./coded.txt";
		std::string oFile = "./decoded.txt";
		writeAllBytes<int8_t>(A.decrypt(readAllBytes<int64_t>(iFile)), oFile);
	}
	else abort();

	return EXIT_SUCCESS;
}