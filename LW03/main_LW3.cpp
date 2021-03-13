#include <vector>
#include <string>
#include <iostream>
#include <fstream>

int main()
{
	//Вариант на 4 = 13;
	std::string part = ".txt";
	size_t m, n;
	std::cout << "Size of table: ";
	std::cin >> n >> m;
	std::vector<std::vector<char>> table;
	table.resize(m);
	std::vector<char> buff;
	std::ifstream iFile("./input" + part, std::ios::binary);
	std::ofstream oFile("./coding" + part, std::ios::binary);
	char *sumbol = new char;
	bool flag = true;

	// coding
	while (flag)
	{
		for (size_t i = 0; i < n; ++i)
		{
			for (size_t j = 0; j < m; ++j)
			{
				if (iFile.read(sumbol, sizeof(char)))
				{
					table[j].push_back(*sumbol);
				}
				else
				{
					flag = false;
					break;
				}
			}
		}

		for (size_t i = 0; i < table.size(); ++i)
		{
			for (size_t j = 0; j < table[i].size(); ++j)
			{
				oFile.write((char*)&table[i][j], sizeof(char));
			}
			table[i].clear();
		}
	}


	//decoding
	table.clear();
	table.resize(n);
	flag = true;
	iFile.close();
	iFile.open("./coding" + part, std::ios::binary);
	oFile.close();
	oFile.open("./decoding" + part, std::ios::binary);

	while (flag)
	{
		buff.clear();
		size_t k = 0;
		for (size_t i = 0; i < n * m; i++)
		{
			if (iFile.read(sumbol, sizeof(char)))
			{
				buff.push_back(*sumbol);
			}
			else
			{
				flag = false;
				break;
			}
		}

		if (!flag)
		{
			size_t sizeBuff = buff.size();
			size_t fullRows = sizeBuff / m;
			long int inLastRows = sizeBuff % m;
			size_t high = fullRows + 1;
			for (size_t i = 0; i < m; ++i)
			{
				if (--inLastRows < 0)
				{
					high = fullRows;
				}

				for (size_t j = 0; j < high; ++j)
				{
					table[j].push_back(buff[k++]);
				}
			}
		}
		else
		{
			for (size_t i = 0; i < m; ++i)
			{
				for (size_t j = 0; j < n; ++j)
				{
					table[j].push_back(buff[k++]);
				}
			}
		}

		for (size_t i = 0; i < table.size(); i++)
		{
			for (size_t j = 0; j < table[i].size(); ++j)
			{
				oFile.write((char*)&table[i][j], sizeof(char));
			}
			table[i].clear();
		}
	}


	delete sumbol;
	iFile.close();
	oFile.close();

	return EXIT_SUCCESS;
}