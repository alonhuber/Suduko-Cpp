#include "stdafx.h"
#include "Square.h"


Square::Square()
{
}

Square::Square(int value, int x, int y)
{
	m_value = value;
	m_x = x;
	m_y = y;
}


Square::~Square()
{
}

void Square::setCache(std::vector<Square*> cache, CacheType type)
{
	for (auto itr=cache.begin();itr!=cache.end();itr++)
	{
		if ((*itr)== this)
		{
			cache.erase(itr);
		switch (type)
		{
		case Square::Row:
			m_row = cache;
			break;
		case Square::Line:
			m_line = cache;
			break;
		case Square::Area:
			m_area = cache;
			break;
		default:
			break;
		}
			break;
		}
	}
}

bool Square::setValue(int value,std::string foundBy)
{
	if (!isHasValue())
	{
		m_value = value;
		std::cout << "Found value with " << foundBy << " on spot:" << m_y << "," << m_x << " value is:" << value << std::endl;
	}
	else
		std::cout << "Can't put value on spot:" << m_y << "," << m_x << std::endl;
	return !isHasValue();
}

void Square::reset()
{
	m_validValues = m_defaultValidValues;
}

void Square::removeValidValue(Square * square)
{
	removeValidValue(square->m_value);	
}

void Square::setDefaultValidValues(int gridSize)
{
	for (int i = 1; i <= gridSize; i++)
		m_defaultValidValues.push_back(i);
}

void Square::solve()
{	
	if (isHasValue())
		return;
	getCacheInfo(m_line);
	if (isHasValue())
		return;
	getCacheInfo(m_area);
	if (isHasValue())
		return;
	getCacheInfo(m_row);
	
}

void Square::getCacheInfo(std::vector<Square*> cache)
{
	for each (auto square in cache)
	{
		removeValidValue(square);
		if (m_validValues.size() == 1)
		{
			setValue(m_validValues[0], "square");
			return;
		}
		else if (m_validValues.size() == 0)
			std::cout << "?";
		
	}
}

void Square::removeValidValue(int value)
{
	if (value != -1)
	{
		auto itr = find(m_validValues.begin(), m_validValues.end(), value);
		if (itr != m_validValues.end())
			m_validValues.erase(itr);
	}
}


int Square::m_gridSize = 0;
std::vector<int> Square::m_defaultValidValues= std::vector<int>();