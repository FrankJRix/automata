/*
#include <automata/grid.h>
#include <automata/lodepng.h>
#include <iostream>

#define WEIRDNESS 1

Grid::Grid(size_t width, size_t heigth)
	: m_width{width}
	, m_heigth{heigth}
	, m_data(width * heigth)
{
}

int Grid::getValue(size_t x, size_t y)
{
	x = ((x % m_width) + m_width) % m_width;
	y = ((y % m_heigth) + m_heigth) % m_heigth;
	return m_data[x + y * m_width];
}

template<typename T>
void Grid::setValue(size_t x, size_t y, T value)
{
	x = ((x % m_width) + m_width) % m_width;
	y = ((y % m_heigth) + m_heigth) % m_heigth;
	m_data[x + y * m_width] = value;
}

size_t Grid::getWidth()
{
	return m_width;
}

size_t Grid::getHeigth()
{
	return m_heigth;
}

void Grid::display()
{
	for(int j{ 0 }; j < m_heigth; j++)
	{
		for(int i{ 0 }; i < m_width; i++)
		{
			if(getValue(i, j) == 0) std::cout << "░░";
			else if(getValue(i, j) == 1) std::cout << "▓▓";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}

void Grid::savePNG()
{
	std::vector<unsigned char> temp;
	temp.resize(m_width * m_heigth);

	for(int j{ 0 }; j < m_heigth; j++)
	{
		for(int i{ 0 }; i < m_width; i++)
		{
			temp[i + j * m_width] = static_cast<unsigned char>(getValue(i, j) * 255);
			//temp[3 * i + 3 * j * m_width + 1] = static_cast<unsigned char>(getValue(i, j) * 255);
			//temp[3 * i + 3 * j * m_width + 2] = static_cast<unsigned char>(getValue(i, j) * 255);
		}
	}
	
	unsigned error = lodepng::encode("output/out.png", temp, m_width, m_heigth, LCT_GREY);
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

void Grid::saveWeirdPNG()
{
	std::vector<unsigned char> temp;
	temp.resize(m_width * m_heigth * 3);

	for(int j{ 0 }; j < m_heigth; j++)
	{
		for(int i{ 0 }; i < m_width; i++)
		{
			temp[3 * i + 3 * j * m_width + 0] = static_cast<unsigned char>(getValue(i + WEIRDNESS*2, j) * 255);
			temp[3 * i + 3 * j * m_width + 1] = static_cast<unsigned char>(getValue(i, j + WEIRDNESS*2) * 255);
			temp[3 * i + 3 * j * m_width + 2] = static_cast<unsigned char>(getValue(i - WEIRDNESS, j - WEIRDNESS) * 255);
		}
	}
	
	unsigned error = lodepng::encode("output/outW.png", temp, m_width, m_heigth, LCT_RGB);
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

template<typename U>
bool operator==(const Grid<U>& g1, const Grid<U>& g2)
{
	return g1.m_data == g2.m_data;
}
*/
