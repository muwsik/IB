#include <utility>
#include <cmath>
#include <ctime>

long int random(long int min, long int max)		//[min, max)
{
	//srand(123);
	srand(static_cast<unsigned int>(time(nullptr)));
	return min + rand() % ((max + 1) - min);
}

bool isSimple(long int x) {
	for (int i = 2; i < sqrt(x); i++)
	{
		if (x%i == 0)
			return true;
	}
	return false;
}

long int GCD(long int a, long int b)
{
	int r = 0;
	int aA = a;
	int bB = b;
	if (a < b)
	{
		aA = b;
		bB = a;
	}
	while (bB != 0)
	{
		r = aA % bB;
		aA = bB;
		bB = r;
	}
	return aA;
}

bool Prime(long int a, long int b)
{
	return GCD(a, b) == 1;
}

struct vector_t 
{
	long int gcd, x, y;
};

vector_t evklidSolve(long int a, long int b)
{
	vector_t U = { a, 1, 0 }, V = { b, 0, 1 };
	while (V.gcd != 0)
	{
		int q = U.gcd / V.gcd;
		vector_t T = { U.gcd % V.gcd, U.x - q * V.x, U.y - q * V.y };
		U = V;
		V = T;
	}
	return U;
}

long int modulePow(long int a, long int b, long int c)
{
	long int x = 1;
	long int y = a;
	while (b > 0)
	{
		if (b % 2 == 1)
		{
			x = (x*y) % c;
		}
		y = (y*y) % c;
		b /= 2;
	}
	return x%c;
}