#pragma once

#include <vector>
#include <fstream>
#include <iostream>

#define BYTES_COUNT 16
#define OFFSET ((BYTES_COUNT)/2)

class Block128
{
public:

	Block128() :left(0), right(0)
	{	}

	Block128(uint64_t left, uint64_t right) : left(left), right(right)
	{	}

	explicit Block128(const uint8_t *data)
	{
		memcpy(&left, data, OFFSET);
		memcpy(&right, data + OFFSET, OFFSET);
	}

	/*explicit Block64(uint8_t *data)
	{
		if (block8 != nullptr)
			delete block8;
		block8 = new Block64::Block8(data);
	}*/

	Block128 swap()
	{
		return *this = { this->right, this->left };
	}

	uint64_t &getLeft()
	{
		return this->left;
	}

	uint64_t &getRight()
	{
		return this->right;
	}

	void writeIn(std::ofstream &stream) const
	{
		stream.write(reinterpret_cast<const char *>(&this->left), OFFSET);
		stream.write(reinterpret_cast<const char *>(&this->right), OFFSET);
	}

	~Block128()
	{	}

	class Block128_u8
	{
		uint8_t *data = nullptr;

		void initParts(uint64_t partA, uint64_t partB)
		{
			if (data != nullptr)
				delete[] data;

			data = new uint8_t[BYTES_COUNT];
			memcpy(data, &partA, sizeof(partA));
			memcpy(data + OFFSET, &partB, sizeof(partB));
		}

	public:
		Block128_u8() : data(nullptr)
		{	}

		explicit Block128_u8(uint8_t *data)
		{
			this->data = new uint8_t[BYTES_COUNT];
			if (data == nullptr) {
				std::cout << "Error!\a\n";
				initParts(0, 0);
			}
			memcpy(this->data, data, BYTES_COUNT);
		}

		Block128_u8(const Block128 &obj)
		{
			this->initParts(obj.left, obj.right);
		}

		Block128_u8(const Block128::Block128_u8 & obj)
		{
			if (this->data != nullptr)
				delete[] data;
			this->data = new uint8_t[BYTES_COUNT];
			memcpy(this->data, obj.data, BYTES_COUNT);
		}

		uint64_t getLeft() const
		{
			uint64_t *part = (uint64_t *)data;
			return *part;
		}

		uint64_t getRight() const
		{
			uint64_t *part = (uint64_t *)(data + OFFSET);
			return *part;
		}

		uint8_t *getData() const
		{
			return this->data;
		}

		void swap()
		{
			uint64_t partLeft = this->getLeft();
			uint64_t partRight = this->getRight();
			memcpy(data, &partRight, sizeof(partRight));
			memcpy(data + OFFSET, &partLeft, sizeof(partLeft));
		}

		virtual ~Block128_u8()
		{
			if (data != nullptr)
				delete[] data;
		}
	};

private:
	uint64_t left;
	uint64_t right;
};


#define BLOCK_SIZE 128
#define KEY_SIZE 256
#define STEPS 16

class Encryption
{
private:

	uint64_t key[4];

	const uint64_t table[16][16] =
	{
		{ 0x4,0xa,0x9,0x2,0xd,0x8,0x0,0xe,0x6,0xb,0x1,0xc,0x7,0xf,0x5,0x3 },
		{ 0xe,0xb,0x4,0xc,0x6,0xd,0xf,0xa,0x2,0x3,0x8,0x1,0x0,0x7,0x5,0x9 },
		{ 0x5,0x8,0x1,0xd,0xa,0x3,0x4,0x2,0xe,0xf,0xc,0x7,0x6,0x0,0x9,0xb },
		{ 0x7,0xd,0xa,0x1,0x0,0x8,0x9,0xf,0xe,0x4,0x6,0xc,0xb,0x2,0x5,0x3 },
		{ 0x6,0xc,0x7,0x1,0x5,0xf,0xd,0x8,0x4,0xa,0x9,0xe,0x0,0x3,0xb,0x2 },
		{ 0x4,0xb,0xa,0x0,0x7,0x2,0x1,0xd,0x3,0x6,0x8,0x5,0x9,0xc,0xf,0xe },
		{ 0xd,0xb,0x4,0x1,0x3,0xf,0x5,0x9,0x0,0xa,0xe,0x7,0x6,0x8,0x2,0xc },
		{ 0x1,0xf,0xd,0x0,0x5,0x7,0xa,0x4,0x9,0x2,0x3,0xe,0x6,0xb,0x8,0xc },
		{ 0x7,0xf,0xd,0x0,0x5,0x1,0xa,0x4,0x9,0x2,0x3,0xe,0x6,0xb,0x8,0xc },
		{ 0x1,0xa,0xd,0x0,0xb,0x7,0xf,0x4,0x9,0x2,0x3,0xe,0x6,0x5,0x8,0xc },
		{ 0x1,0xc,0xd,0x0,0x5,0x7,0xa,0x4,0x9,0x2,0x3,0xe,0x6,0xb,0x8,0xf },
		{ 0x8,0xf,0xd,0x0,0x5,0x7,0xa,0x4,0x9,0x2,0x3,0xe,0x6,0xb,0x1,0xc },
		{ 0x5,0xf,0x1,0xd,0xa,0x3,0x4,0x2,0xe,0x8,0xc,0x7,0x6,0x0,0x9,0xb },
		{ 0x4,0x5,0x9,0x2,0xd,0x8,0x0,0xe,0x6,0xb,0x1,0xc,0x3,0xf,0xa,0x7 },
		{ 0x4,0xa,0x9,0xf,0xd,0x8,0x0,0xe,0x6,0xb,0x1,0xc,0x7,0x2,0x5,0x3 },
		{ 0x4,0xa,0x9,0x2,0xd,0x8,0x0,0xe,0x3,0xb,0x1,0xc,0x7,0x5,0xf,0x6 },
	};

	uint64_t ReplaceBlock(uint64_t x)
	{
		struct uint_4bit
		{
			uint64_t bit4 : 4;
		} part = { 0 };
		uint64_t result = 0ULL;

		for (int i = 15; i >= 0; i--)
		{
			part.bit4 = x >> (i * 4);
			part.bit4 = table[i][part.bit4];
			result = (result << 4) | part.bit4;
		}
		return uint64_t(result);
	}

	Block128 MainStep(Block128 N, uint64_t x)
	{
		uint64_t S = 0ULL;
		S = N.getRight() + x;
		S = ReplaceBlock(S);
		S = (S << 11) | (S >> 53);
		S ^= N.getLeft();
		return{ N.getRight(), S };
	}

	const int Z_R[16] = { 0, 1, 2, 3,		 0, 1, 2, 3,		0, 1, 2, 3,		 3, 2, 1, 0 };

public:

	Encryption(std::string fileName)
	{
		std::ifstream file(fileName, std::ios::binary);
		for (size_t i = 0; i < 4; i++)
		{
			file.read((char*)&this->key[i], sizeof(uint64_t));
		}
		file.close();
	}

	Block128 Encrypt(Block128 block, bool flag)
	{
		if (flag)
		{
			for (int i = 0; i < STEPS; i++)
			{
				block = this->MainStep(block, key[Z_R[i]]);
			}
		}
		else
		{
			for (int i = STEPS - 1; i >= 0; i--)
			{
				block = this->MainStep(block, key[Z_R[i]]);
			}
		}
		return block.swap();
	}

	~Encryption()
	{	}
};