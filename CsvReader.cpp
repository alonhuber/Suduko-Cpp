#include "stdafx.h"
#include "CsvReader.h"


CsvReader::CsvReader()
{
}


CsvReader::~CsvReader()
{
}

SquareGrid CsvReader::getGrid(std::string path)
{
	std::ifstream file(path);

	SquareGrid dataList;
	std::string delimeter = ",";
	std::string line = "";
	// Iterate through each line and split the content using delimeter
	try
	{
		int y = 0;
		while (getline(file, line))
		{
			int x = 0;
			y++;
			std::vector<std::string> vec;
			std::vector<Square*> squareVec;
			boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
			for each (std::string var in vec)
			{
				x++;
				int value;
				if (var != "")
					value = std::stoi(var);
				else
					value = -1;
				Square* square= new Square(value,x,y);
				squareVec.push_back(square);
			}			
			dataList.push_back(squareVec);
		}
	}
	catch (std::invalid_argument err)
	{
		std::cout << err.what() << std::endl;
		return SquareGrid();
	}
	// Close the File
	file.close();
	return dataList;
}
