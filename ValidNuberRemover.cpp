#include "stdafx.h"
#include "ValidNuberRemover.h"


ValidNuberRemover::ValidNuberRemover()
{
}


ValidNuberRemover::~ValidNuberRemover()
{
}

void ValidNuberRemover::removeValidNumbers(std::vector<Square*> group)
{
	group = removeSquareWithValue(group);
	auto originalGroup = group;
	//Check for group from 2 to group size-1 groups of valid numbers to remove
	for (int i = 2; i < group.size(); i++)
	{
		auto miniGroupToValues=runOnGroup(group, std::vector<Square*>(), i - 1);
		for (auto pair : miniGroupToValues)
		{
			std::vector<Square*> groupToRemoveValid = removeSquareThatPartOfMiniGroup(originalGroup, pair.first);
			group=removeSquareThatPartOfMiniGroup(group,pair.first);
			for (auto square : groupToRemoveValid)
			{
				for (auto value : pair.second)
					square->removeValidValue(value);
			}
		}
	}
}

void ValidNuberRemover::removeValidNumbers(SquareGrid area)
{
	std::vector<Square*> group;
	for (auto line : area)
		group.insert(group.begin(), line.begin(), line.end());
	removeValidNumbers(group);
}

std::vector<Square*> ValidNuberRemover::removeSquareWithValue(std::vector<Square*> group)
{
	for (auto itr = group.begin(); itr != group.end();)
	{
		if ((*itr)->isHasValue())
			itr = group.erase(itr);
		else
			itr++;
	}
	return group;
}

std::vector<Square*> ValidNuberRemover::removeSquareThatPartOfMiniGroup(std::vector<Square*> group, std::vector<Square*> miniGroup)
{
	for (auto itr = group.begin(); itr != group.end();)
	{
		if (std::find(miniGroup.begin(), miniGroup.end(), (*itr)) != miniGroup.end())
			itr = group.erase(itr);
		else
			itr++;
	}
	return group;
}

std::vector<std::pair<std::vector<Square*>, std::vector<int>>> ValidNuberRemover::runOnGroup(std::vector<Square*> groupToRun, std::vector<Square*> squaresToCheck, int depthToGo)
{
	std::vector<std::pair<std::vector<Square*>, std::vector<int>>> miniGroupToValues;
	for (auto itr=groupToRun.begin();itr!=(groupToRun.end()-depthToGo);itr++)
	{
		auto squaresToCheckIncludeLastIterate = squaresToCheck;
		if (depthToGo == 0)
		{
			squaresToCheckIncludeLastIterate.push_back(*itr);
			std::set<int> validNumbers;
			for (auto square : squaresToCheckIncludeLastIterate)
			{
				for (auto validValue : square->m_validValues)
				{
					validNumbers.insert(validValue);
					if (validNumbers.size() > squaresToCheckIncludeLastIterate.size())
						break;
				}
				if (validNumbers.size() > squaresToCheckIncludeLastIterate.size())
					break;
			}

			if (validNumbers.size() <= squaresToCheckIncludeLastIterate.size())
			{
				miniGroupToValues.push_back(std::pair<std::vector<Square*>, std::vector<int>>(squaresToCheckIncludeLastIterate,
					std::vector<int>(validNumbers.begin(),validNumbers.end())));
				return miniGroupToValues;
			}
		}
		else
		{
			std::vector<Square*> newGroupToRun(itr+1,groupToRun.end());
			squaresToCheckIncludeLastIterate.push_back(*itr);
			auto vec = runOnGroup(newGroupToRun, squaresToCheckIncludeLastIterate, depthToGo - 1);
			miniGroupToValues.insert(miniGroupToValues.begin(), vec.begin(),vec.end());
		}
	}
	return miniGroupToValues;
}
