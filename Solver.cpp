#include "stdafx.h"
#include "Solver.h"
#include "CsvReader.h"

Solver::Solver()
{
	
}


Solver::~Solver()
{
	for (auto& line : m_grid)
	{		
		for (auto& square : line)
			delete square;
	}
}

bool Solver::solve(std::string path, std::string outputPath)
{
	CsvReader reader;
	m_grid = reader.getGrid(path);
	Square::m_gridSize = m_grid.size();
	m_complemenarySquareFinder.setGridSize(m_grid.size());
	setCachedVectors();
	int count = 0;
	while (true)
	{
		count++;
		std::cout << "Turn number:" << count << std::endl;
		SolvingStatus status = getSolvingStatus();
		if (status == SolvingStatus::Succeeded)
		{
			writeSolution(outputPath);
			return true;
		}
		else if (status == SolvingStatus::Stuck)
		{
			writeSolution(outputPath);
			std::cout << "Can't solve this suduko" << std::endl;
			return false;
		}

		for (auto& line : m_grid)
		{
			m_tracker.findOneSquareWithValidNumber(line);
			m_remover.removeValidNumbers(line);
			for (auto& square : line)
				square->solve();
		}

		//m_complemenarySquareFinder.findComplemenarySquare(m_grid, m_upsideDownGrid,false);
		//m_complemenarySquareFinder.findComplemenarySquare(m_upsideDownGrid,m_grid,true);
		for (auto row : m_upsideDownGrid)
		{
			m_tracker.findOneSquareWithValidNumber(row);
			m_remover.removeValidNumbers(row);
		}
		for (auto areaGrid : m_areasGrid)
		{
			for (auto area : areaGrid)
			{
				m_tracker.findOneSquareWithValidNumber(area);
				m_remover.removeValidNumbers(area);
			}
		}
	}

}

void Solver::setCachedVectors()
{	 
	int gridSize = m_grid.size();
	Square::setDefaultValidValues(gridSize);
	m_areasGrid.resize(std::sqrt(gridSize));
	m_upsideDownGrid.resize(gridSize);
	for (auto & area : m_areasGrid)
		area.resize(std::sqrt(gridSize));

	for(int i = 0; i < gridSize;i++)
	{
		for(int j=0;j<gridSize;j++)
		{
			Square* square= m_grid[i][j];			
			m_upsideDownGrid[j].push_back(square);
			//For example(9x9): 0-2 is the first area 3-5 is the second 6-8 is the third
			// i=3 j=6 is in the 1,2 area
			m_areasGrid[i / std::sqrt(gridSize)][j / std::sqrt(gridSize)].push_back(square);
			square->reset();
		}
	}

	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j<gridSize; j++)
		{
			Square* square = m_grid[i][j];
			square->setCache(m_grid[i], Square::CacheType::Line);
			square->setCache(m_upsideDownGrid[j], Square::CacheType::Row);
			square->setCache(m_areasGrid[i / std::sqrt(m_grid.size())][j / std::sqrt(m_grid.size())], Square::CacheType::Area);
		}
	}	
}

SolvingStatus Solver::getSolvingStatus()
{
	static int LastMissingNumbers = -1;
	int missingNumbers = 0;
	for each (auto line in m_grid)
	{
		for each (auto square in line)
			square->isHasValue() ? true:missingNumbers++;
	}
	SolvingStatus status;
	if (missingNumbers == 0)
		status = SolvingStatus::Succeeded;
	else if (missingNumbers == LastMissingNumbers)
		status = SolvingStatus::Stuck;
	else
		status = SolvingStatus::Progress;
	LastMissingNumbers = missingNumbers;
	return status;
}

void Solver::writeSolution(std::string outputPath)
{
	std::string delimeter = ",";
	std::ofstream file(outputPath);
	std::string data;
	for (auto line : m_grid)
	{
		for (auto square : line)
			data += std::to_string(square->getValue()) + delimeter;
		data.pop_back();
		data += "\n";
	}
	file << data;
}
