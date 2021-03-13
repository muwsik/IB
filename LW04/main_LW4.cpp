#include "LW_4.h"

Block128 readBlock(std::ifstream &stream)
{
	std::vector<uint8_t> result(BYTES_COUNT);
	stream.read(reinterpret_cast<char *>(&result[0]), BYTES_COUNT);
	return Block128(&result[0]);
}

size_t getCountBlocks(std::string nameFile, uint8_t &remainder)
{
	std::ifstream ifs(nameFile, std::ios::binary | std::ios::ate);
	remainder = BYTES_COUNT - (ifs.tellg() % BYTES_COUNT); // количество символов, которое надо удалить после расшифровки
	return static_cast<size_t>(ifs.tellg() / BYTES_COUNT); // количество блоков по 16 байт (128 бит)
}

void writeBlockInBytes(std::ofstream &stream, const Block128 &block, uint8_t remainder = 0)
{
	Block128::Block128_u8 result(block);
	stream.write(reinterpret_cast<const char *>(result.getData()), BYTES_COUNT - remainder);
}


int main(void)
{
	std::string expansion = ".png";
	std::string nameFileKey = "./key.txt";
	std::string nameFileInput = "./input" + expansion;
	std::string nameFileCoding = "./coding.txt";
	std::string nameFileDecoding = "./decoding" + expansion;

	Encryption Temp(nameFileKey);
	char Q; std::ifstream iFile; std::ofstream oFile;
	uint8_t remainder; size_t countBlocks;

	std::cout << "Encode? (y/n)\n> ";
	std::cin >> Q;
	if (Q == 'y')
	{
		iFile.open(nameFileInput, std::ios::binary);
		oFile.open(nameFileCoding, std::ios::binary);
		countBlocks = getCountBlocks(nameFileInput, remainder);
		oFile.write(reinterpret_cast<const char *>(&remainder), sizeof(remainder));

		for (size_t i = 0; i <= countBlocks; i++)
		{
			Block128 Block = readBlock(iFile);
			Block = Temp.Encrypt(Block, true);
			Block.writeIn(oFile);
		}
		std::cout << "Successfully encoded!" << std::endl;
	}
	else if (Q == 'n')
	{
		iFile.open(nameFileCoding, std::ios::binary);
		countBlocks = getCountBlocks(nameFileCoding, remainder);
		iFile.read(reinterpret_cast<char *>(&remainder), sizeof(remainder));
		oFile.open(nameFileDecoding, std::ios::binary);

		Block128 Block;
		for (size_t i = 0; i < countBlocks - 1; i++)
		{
			Block = readBlock(iFile);
			Block = Temp.Encrypt(Block, false);
			Block.writeIn(oFile);
		}
		Block = readBlock(iFile);
		Block = Temp.Encrypt(Block, false);
		writeBlockInBytes(oFile, Block, remainder);
		std::cout << "Successfully decoded!" << std::endl;
	}
	else abort();

	return EXIT_SUCCESS;
}