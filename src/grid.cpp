#include <automata/grid.h>
#include <automata/lodepng.h>
#include <iostream>

#define WEIRDNESS 1

Grid::Grid(int width, int heigth)
	: m_width{width}
	, m_heigth{heigth}
{
	m_data.resize(width * heigth);
}
/*
Grid::Grid(const Grid &old)
	: m_width{old.m_width}
	, m_heigth{old.m_heigth}
	, m_data{old.m_data}
{
}
*/
int Grid::getValue(int x, int y)
{
	x = ((x % m_width) + m_width) % m_width;
	y = ((y % m_heigth) + m_heigth) % m_heigth;
	return m_data[x + y * m_width];
}

void Grid::setValue(int x, int y, int value)
{
	x = ((x % m_width) + m_width) % m_width;
	y = ((y % m_heigth) + m_heigth) % m_heigth;
	m_data[x + y * m_width] = value;
}

int Grid::getWidth()
{
	return m_width;
}

int Grid::getHeigth()
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
	temp.resize(m_width * m_heigth * 3);

	for(int j{ 0 }; j < m_heigth; j++)
	{
		for(int i{ 0 }; i < m_width; i++)
		{
			temp[3 * i + 3 * j * m_width + 0] = static_cast<unsigned char>(getValue(i, j) * 255);
			temp[3 * i + 3 * j * m_width + 1] = static_cast<unsigned char>(getValue(i, j) * 255);
			temp[3 * i + 3 * j * m_width + 2] = static_cast<unsigned char>(getValue(i, j) * 255);
		}
	}
	
	unsigned error = lodepng::encode("output/out.png", temp, m_width, m_heigth, LCT_RGB);
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

bool operator==(const Grid &g1, const Grid &g2)
{
	return g1.m_data == g2.m_data;
}
