#include <iostream>
#include <fstream>
#include <string>
#include <ctime>


uint64_t powMod(uint64_t n, uint64_t x, uint64_t p);

int main(void)
{
	srand(time(nullptr)); 

	uint64_t p = 13669, g = 7;
	uint64_t Xa = rand();//, Xb = rand();
	//std::cout << "Xa: " << Xa << "; Xb: " << Xb << std::endl;

	uint64_t Ya = powMod(g, Xa, p);
	
	uint64_t Yb;// = powMod(g, Xb, p);
	std::cout << "Ya: " << Ya;// << "; Yb: " << powMod(g, Xb, p) << std::endl;
	std::cin >> Yb;
	uint64_t Zab = powMod(Yb, Xa, p);
	//uint64_t Zba = powMod(Ya, Xb, p);
	std::cout << "Zab: " << Zab;// << "; Zba: " << Zba << std::endl;

	char Q;
	std::cout << "Encode? (y/n)\n> ";	std::cin >> Q;

	if (Q == 'y')
	{
		std::ifstream iFile("./input.txt", std::ios::binary);
		std::ofstream oFile("./coding.txt", std::ios::binary);

		char buff;
		while (iFile.read(reinterpret_cast<char *>(&buff), sizeof(char)))
		{
			char result = buff ^ Zab;
			oFile.write(reinterpret_cast<const char*>(&result), sizeof(char));
		}
		std::cout << "Successfully encoded!" << std::endl;
	}
	else if (Q == 'n')
	{
		std::ifstream iFile("./coding.txt", std::ios::binary);
		std::ofstream oFile("./decoding.txt", std::ios::binary);

		char buff;
		while (iFile.read(reinterpret_cast<char *>(&buff), sizeof(char)))
		{
			char result = buff ^ Zab;
			oFile.write(reinterpret_cast<const char*>(&result), sizeof(char));
		}
		std::cout << "Successfully decoded!" << std::endl;
	}
	else abort();

	return EXIT_SUCCESS;
}

uint64_t powMod(uint64_t n, uint64_t x, uint64_t p)
{
	uint64_t count = 1;
	if (x == 0)
		return 1;
	while (x > 0)
	{
		if (x % 2 == 0)
		{
			x /= 2;
			n *= n;
			n %= p;
		}
		else
		{
			x--;
			count *= n;
			count %= p;
		}
	}
	return count %p;
}