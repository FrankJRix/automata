#ifndef GRID_H
#define GRID_H
#include <vector>
#include <automata/lodepng.h>
#include <iostream>

#define WEIRDNESS 1

template <typename T>
class Grid
{
protected:
	std::size_t m_width;
	std::size_t m_heigth;
	std::vector<T> m_data;
public:
	Grid(std::size_t width, std::size_t heigth)
	: m_width{width}
	, m_heigth{heigth}
	, m_data(width * heigth)
	{
	}

	void display()
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

	void savePNG()
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

	void saveWeirdPNG()
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

	// operators
	template <typename U>
	friend bool operator==(const Grid<U>& g1, const Grid<U>& g2)
	{
		return g1.m_data == g2.m_data;
	}

	// setters and getters
	T getValue(std::size_t x, std::size_t y)
		{
		x = ((x % m_width) + m_width) % m_width;
		y = ((y % m_heigth) + m_heigth) % m_heigth;
		return m_data[x + y * m_width];
		}

	void setValue(std::size_t x, std::size_t y, T value)
	{
		x = ((x % m_width) + m_width) % m_width;
		y = ((y % m_heigth) + m_heigth) % m_heigth;
		m_data[x + y * m_width] = value;
	}

	std::size_t getWidth()
	{
		return m_width;
	}

	std::size_t getHeigth()
	{
		return m_heigth;
	}
};

/*
// Implementation from here.

#include <automata/lodepng.h>
#include <iostream>

#define WEIRDNESS 1

template <typename T>
Grid<T>::Grid(size_t width, size_t heigth)
	: m_width{width}
	, m_heigth{heigth}
	, m_data(width * heigth)
{
}

template <typename T>
int Grid<T>::getValue(size_t x, size_t y)
{
	x = ((x % m_width) + m_width) % m_width;
	y = ((y % m_heigth) + m_heigth) % m_heigth;
	return m_data[x + y * m_width];
}

template<typename T>
void Grid<T>::setValue(size_t x, size_t y, T value)
{
	x = ((x % m_width) + m_width) % m_width;
	y = ((y % m_heigth) + m_heigth) % m_heigth;
	m_data[x + y * m_width] = value;
}

template <typename T>
size_t Grid<T>::getWidth()
{
	return m_width;
}

template <typename T>
size_t Grid<T>::getHeigth()
{
	return m_heigth;
}

template <typename T>
void Grid<T>::display()
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

template <typename T>
void Grid<T>::savePNG()
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

template <typename T>
void Grid<T>::saveWeirdPNG()
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

#endif