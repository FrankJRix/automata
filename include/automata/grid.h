#ifndef GRID_H
#define GRID_H
#include <vector>

class Grid
{
protected:
	int m_width;
	int m_heigth;
	std::vector<int> m_data{};
public:
	Grid(int width, int heigth);
	//Grid(const Grid& old);
	void display();
	void savePNG();
	void saveWeirdPNG();

	// operators
	friend bool operator==(const Grid& g1, const Grid& g2);

	// setters and getters
	int getValue(int x, int y);
	void setValue(int x, int y, int value);

	int getWidth();
	int getHeigth();
};

#endif