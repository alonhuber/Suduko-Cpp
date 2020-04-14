#pragma once
#include "Square.h"
//Whenever find group of n squares with n valid numbers total it can remove from the other group(cache) squares
class ValidNuberRemover
{
public:
	ValidNuberRemover();
	~ValidNuberRemover();
	void removeValidNumbers(std::vector<Square*> group);
	void removeValidNumbers(SquareGrid area);
	void setGridSize(int size) { m_gridSize = size; }
private:
	std::vector<Square*> removeSquareWithValue(std::vector<Square*> group);
	std::vector<Square*> removeSquareThatPartOfMiniGroup(std::vector<Square*> group, std::vector<Square*> miniGroup);
	//run on the vector of the group and find the valid numbers recoursive(run on the every combinaiton of the vector) 
	std::vector<std::pair<std::vector<Square*>, std::vector<int>>> runOnGroup(std::vector<Square*> groupToRun,std::vector<Square*> squaresToCheck, int depthToGo);
	int m_gridSize;
};

