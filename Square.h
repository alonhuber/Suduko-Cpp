#pragma once
class Square
{
public:
	enum CacheType
	{
		Row,
		Line,
		Area
	};
	Square();
	Square(int value,int x, int y);
	~Square();
	void setCache(std::vector<Square*> cache,CacheType type);
	bool isHasValue() { return m_value != -1; }
	int getValue() { return m_value; }
	bool setValue(int value,std::string foundBy);
	void reset();
	void removeValidValue(Square* square);
	static void setDefaultValidValues(int gridSize);
	void solve();
	void getCacheInfo(std::vector<Square*> cache);
	void removeValidValue(int value);
	std::vector<int> m_validValues;
	static int m_gridSize;
private:
	int m_value;
	int m_x, m_y;
	std::vector<Square*> m_row, m_line, m_area;
	static std::vector<int> m_defaultValidValues;

};

