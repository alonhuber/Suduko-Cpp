#include "stdafx.h"
#include "ComplemenarySquareFinder.h"


ComplemenarySquareFinder::ComplemenarySquareFinder()
{
}


ComplemenarySquareFinder::~ComplemenarySquareFinder()
{
}
void ComplemenarySquareFinder::findComplemenarySquare(SquareGrid grid, SquareGrid upsideGrid, bool isUpdside)
{
	//Iterate the number between 1 to the largest option
	for (int value = 1; value <= grid.size(); value++)
	{
		//Run on the grid in jump of root of the grid size to a one missing line in area 
		for (int i = 0; i < grid.size(); i += m_sqrtGridSize)
		{
			int missingIndex = -1;
			//Find the Missing grid line(the upside one to grid)
			std::vector<int> missingNumberArea;
			missingNumberArea.resize(m_sqrtGridSize);
			std::iota(missingNumberArea.begin(), missingNumberArea.end(), 0);
			for (int j = i; j < i + m_sqrtGridSize; j++)
			{				
				auto itr = std::find_if(grid[j].begin(), grid[j].end(), [value](Square* s) { return s->getValue() == value; });
				if (itr != grid[j].end())
				{
					
					int index = std::distance(grid[j].begin(), itr);
					int area = index / m_sqrtGridSize;
					auto missingItr=std::find(missingNumberArea.begin(), missingNumberArea.end(), area);
					if (missingItr != missingNumberArea.end())
					{
						missingNumberArea.erase(missingItr);
					}
				}
				else
				{
					if (missingIndex!=-1)
						break;
					missingIndex = j;
				}
			}
			//If one missing grid line is left the missing one is the only one who can be with the missing value
			if (missingNumberArea.size() == 1)
			{
				bool isHasMoreThanMissingSpot = false;
				int updsideIndex = -1;
				int area = missingNumberArea[0];
				std::vector<int> missingNumberLineOrRow(m_sqrtGridSize);
				std::iota(missingNumberLineOrRow.begin(), missingNumberLineOrRow.end(), 0);
				//Go to the upsideGrid line that found the iterate of the regular grid and run on the area
				for (int j = area*m_sqrtGridSize; j < (area + 1)*m_sqrtGridSize; j++)
				{
					auto itr = std::find_if(upsideGrid[j].begin(), upsideGrid[j].end(), [value](Square* s) { return s->getValue() == value; });
					//If the line is don't contain the value and the the square who should get the value hasn't has value
					if (itr == upsideGrid[j].end() && !grid[missingIndex][j]->isHasValue())
					{
						//If it found more than one option can't put value on any square
						if (updsideIndex == -1)
							updsideIndex = j;
						else
						{
							isHasMoreThanMissingSpot = true;
							break;
						}
					}
				}
				if (!isHasMoreThanMissingSpot && updsideIndex != -1)
				{	
					grid[missingIndex][updsideIndex]->setValue(value, "comp");
					if (isUpdside)
						std::swap(missingIndex, updsideIndex);					
				}
			}
		}
	}
}
