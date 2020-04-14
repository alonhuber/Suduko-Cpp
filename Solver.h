#pragma once
#include "stdafx.h"
#include "Square.h"
#include "ComplemenarySquareFinder.h"
#include "TrackValueWithValidNumber.h"
#include "ValidNuberRemover.h"
enum SolvingStatus
{
	Succeeded,
	Stuck,
	Progress
};

class Solver
{
public:
	Solver();
	~Solver();
	bool solve(std::string path, std::string outputPath);
private:
	//Set the cache for the solver and the squares
	void setCachedVectors();
	//Check for number of missing square. If there isn't it return it stuck, 
	//if it has 0 missing squares it will return success. Otherwise return in progress
	SolvingStatus getSolvingStatus(); 
	void writeSolution(std::string outputPath);
	//The suduko grid, the upside grid is the same grid with the row and line are switched
	SquareGrid m_grid, m_upsideDownGrid;
	//Contain the areas of the grid
	std::vector<
		SquareGrid>m_areasGrid;
	ComplemenarySquareFinder m_complemenarySquareFinder;
	TrackValueWithValidNumber m_tracker;
	ValidNuberRemover m_remover;
};

