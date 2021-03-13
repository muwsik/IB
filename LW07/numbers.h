#include <utility>
#include <cmath>
#include <ctime>

bool isSimple(int x) {
	for (int i = 2; i < sqrt(x); i++)
	{
		if (x%i == 0)
			return true;
	}
	return false;
}

int GCD(int a, int b)
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

bool Prime(int a, int b)
{
	return GCD(a, b) == 1;
}

struct vector
{
	int gcd, x, y;
};

vector evklidSolve(int a, int b)
{
	vector U = { a, 1, 0 }, V = { b, 0, 1 };
	while (V.gcd != 0)
	{
		int q = U.gcd / V.gcd;
		vector T = { U.gcd % V.gcd, U.x - q * V.x, U.y - q * V.y };
		U = V;
		V = T;
	}
	return U;
}

int64_t module(int64_t a, int64_t b, int64_t c)
{
	int64_t x = 1;
	int64_t y = a;
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