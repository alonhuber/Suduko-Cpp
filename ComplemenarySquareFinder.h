#pragma once
#include "Square.h"
//When there is one line/row in group who missing value it will try to find the missing square 
class ComplemenarySquareFinder
{
public:
	ComplemenarySquareFinder();
	~ComplemenarySquareFinder();
	void findComplemenarySquare(SquareGrid grid, SquareGrid upsideGrid,bool isUpdside);
	void setGridSize(int gridSize) { m_gridSize = gridSize; m_sqrtGridSize = std::sqrt(gridSize); }
private:
	int m_gridSize, m_sqrtGridSize;
};

