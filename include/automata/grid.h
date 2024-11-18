#ifndef GRID_H
#define GRID_H
#include <vector>

template <typename T>
class Grid
{
protected:
	std::size_t m_width;
	std::size_t m_heigth;
	std::vector<T> m_data;
public:
	Grid(std::size_t width, std::size_t heigth);

	void display();
	void savePNG();
	void saveWeirdPNG();

	// operators
	inline friend bool operator==(const Grid<T>& g1, const Grid<T>& g2) {return g1.m_data == g2.m_data;}

	// setters and getters
	T getValue(std::size_t x, std::size_t y);
	void setValue(std::size_t x, std::size_t y, T value);
	std::size_t getWidth();
	std::size_t getHeigth();
};

#endif