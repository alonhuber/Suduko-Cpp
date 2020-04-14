#pragma once
#include "stdafx.h"
#include "Square.h"
//Read the grid from csv
class CsvReader
{
public:
	CsvReader();
	~CsvReader();
	SquareGrid getGrid(std::string path);	
};

