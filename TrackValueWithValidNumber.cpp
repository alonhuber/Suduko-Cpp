#include "stdafx.h"
#include "TrackValueWithValidNumber.h"


TrackValueWithValidNumber::TrackValueWithValidNumber()
{
}


TrackValueWithValidNumber::~TrackValueWithValidNumber()
{
}

void TrackValueWithValidNumber::findOneSquareWithValidNumber(std::vector<Square*> group)
{
	//Value to only square who had this value
	//If value had more than one square or defined value it will contain null 
	std::map<int, Square*> validValueToSquare;
	for (Square* square : group)
	{
		if (!square->isHasValue())
		{
			for (int validValue : square->m_validValues)
			{
				//If the value is found more then once it don't had one square
				if (validValueToSquare.find(validValue) != validValueToSquare.end())
					validValueToSquare[validValue]=nullptr;
				else				
					validValueToSquare[validValue] = square;				
			}
		}
		else
			validValueToSquare[square->getValue()] = nullptr;
	}
	for (auto oneValueSquare : validValueToSquare)
	{
		if(oneValueSquare.second)
			oneValueSquare.second->setValue(oneValueSquare.first,"only one with this valid number");
	}
}

void TrackValueWithValidNumber::findOneSquareWithValidNumber(SquareGrid area)
{
	std::vector<Square*> group;
	for (auto line : area)
		group.insert(group.begin(),line.begin(),line.end());
	findOneSquareWithValidNumber(group);
}
