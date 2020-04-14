#pragma once
#include "Square.h"
//Find in a group(area, row and line) square who is the only square in the group who had this valid number
class TrackValueWithValidNumber
{
public:
	TrackValueWithValidNumber();
	~TrackValueWithValidNumber();

	void findOneSquareWithValidNumber(std::vector<Square*> group);
	//Create vector from the grid and call the first function 
	void findOneSquareWithValidNumber(SquareGrid area);
};

