#include "numbers.h"
#include <iostream>
#include <string>


class RSA
{
public:struct publicKey {
		int d = 0;
		int N = 0;
	} pubKey;
private:

	uint8_t index;
	int f;
	int e;

	int generate(int f)
	{
		for (int i = this->random(10, f / 100); i < f; i++)
		{
			if (Prime(i, f))
			{
				return i;
			}
		}
		return 0;
	}

	int calc(int d, int f)
	{
		vector e = evklidSolve(d, f);
		if (e.x < 0)
		{
			e.x += f;
		}
		return e.x;
	}

	int random(int min, int max)
	{
		srand(time(nullptr));
		return min + rand() % ((max + 1) - min);
	}

public:
	const publicKey &getKey() const {
		return pubKey;
	}

	RSA(uint8_t index, int p = 46817, int q = 45659): index(index)
	{
		this->pubKey.N = p*q;
		this->f = (p - 1)*(q - 1);
		this->pubKey.d = generate(f);
		this->e = calc(pubKey.d, f);
	}

	void inf()
	{
		std::cout << "User #" << (int)index << " have public key: (" 
			<< pubKey.N << " " << pubKey.d
			<< "), private key: " << e << '\n';
	}

	std::vector<int64_t> encrypt(std::vector<int8_t> message,
		publicKey pubKey)
	{
		std::vector<int64_t> result;
		for (auto i : message)
		{
			int64_t c = module(i, pubKey.d, pubKey.N);
			result.push_back(c);
		}
		return result;
	}

	std::vector<int8_t> decrypt(std::vector<int64_t> message)
	{
		std::vector<int8_t> result;
		for (auto i : message)
		{
			int64_t m = module(i, e, this->pubKey.N);
			result.push_back((int8_t)m);
		}
		return result;
	}
};


template <typename T>
std::vector<T> readAllBytes(const std::string &filename)
{
	std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
	std::streampos pos = ifs.tellg();
	std::vector<T> result(static_cast<unsigned long>(pos / sizeof(T)));
	ifs.seekg(0, std::ios::beg);
	ifs.read(reinterpret_cast<char *>(&result[0]), pos);
	return result;
}

template <typename T>
void writeAllBytes(std::vector<T> bytes, const std::string &fileName) {
	std::ofstream outfile(fileName, std::ios::out | std::ios::binary);
	outfile.write(reinterpret_cast<const char *>(&bytes[0]), bytes.size() * sizeof(T));
}