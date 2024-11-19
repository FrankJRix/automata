#include <automata/grid.h>
#include <automata/lodepng.h>
#include <iostream>
#include <algorithm>

#define WEIRDNESS 1

template<typename T>
Grid<T>::Grid(std::size_t width, std::size_t heigth)
	: m_width{width}
	, m_heigth{heigth}
	, m_data(width * heigth)
{
}

template<typename T>
T Grid<T>::getValue(std::size_t x, std::size_t y)
{
	x = ((x % m_width) + m_width) % m_width;
	y = ((y % m_heigth) + m_heigth) % m_heigth;
	return m_data[x + y * m_width];
}

template<typename T>
void Grid<T>::setValue(std::size_t x, std::size_t y, T value)
{
	x = ((x % m_width) + m_width) % m_width;
	y = ((y % m_heigth) + m_heigth) % m_heigth;
	m_data[x + y * m_width] = value;
}

template<typename T>
std::size_t Grid<T>::getWidth()
{
	return m_width;
}

template<typename T>
std::size_t Grid<T>::getHeigth()
{
	return m_heigth;
}

template<typename T>
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

template<typename T>
void Grid<T>::savePNG(std::size_t normalization)
{
	std::vector<unsigned char> temp;
	temp.resize(m_width * m_heigth);

	for(int j{ 0 }; j < m_heigth; j++)
	{
		for(int i{ 0 }; i < m_width; i++)
		{// IT WILL GIVE PROBLEMS: getValue returns T, which might not contain getValue * 255. Maybe it'll sort it out on its own, needs testing.
			temp[i + j * m_width] = static_cast<unsigned char>(getValue(i, j) * 255 / normalization);
			//temp[3 * i + 3 * j * m_width + 1] = static_cast<unsigned char>(getValue(i, j) * 255);
			//temp[3 * i + 3 * j * m_width + 2] = static_cast<unsigned char>(getValue(i, j) * 255);
		}
	}
	
	unsigned error = lodepng::encode("output/out.png", temp, m_width, m_heigth, LCT_GREY);
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

template<typename T>
void Grid<T>::saveWeirdPNG(std::size_t normalization)
{
	std::vector<unsigned char> temp;
	temp.resize(m_width * m_heigth * 3);

	for(int j{ 0 }; j < m_heigth; j++)
	{
		for(int i{ 0 }; i < m_width; i++)
		{// see above ^
			temp[3 * i + 3 * j * m_width + 0] = static_cast<unsigned char>(getValue(i + WEIRDNESS*2, j) * 255 / normalization);
			temp[3 * i + 3 * j * m_width + 1] = static_cast<unsigned char>(getValue(i, j + WEIRDNESS*2) * 255/ normalization);
			temp[3 * i + 3 * j * m_width + 2] = static_cast<unsigned char>(getValue(i - WEIRDNESS, j - WEIRDNESS) * 255/ normalization);
		}
	}
	
	unsigned error = lodepng::encode("output/outW.png", temp, m_width, m_heigth, LCT_RGB);
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

template<typename T>
template<typename U>
Grid<T> &Grid<T>::operator+=(const Grid<U> &rhs)
{
	std::transform( m_data.begin(),
					m_data.end(),
					rhs.m_data.begin(),
					m_data.begin(),
					[](T a, U b)
					{
						return a + b;
					});
	return *this;
}

template <typename T>
Grid<T> &Grid<T>::operator/=(T rhs)
{
	std::transform( m_data.begin(),
					m_data.end(),
					m_data.begin(),
					[rhs](T a)
					{
						return a / rhs;
					});
	return *this;
}

template class Grid<std::uint8_t>;
template class Grid<std::uint32_t>;

template Grid<std::uint8_t>& Grid<std::uint8_t>::operator+=(const Grid<std::uint8_t>&);
template Grid<std::uint32_t>& Grid<std::uint32_t>::operator+=(const Grid<std::uint32_t>&);
template Grid<std::uint8_t>& Grid<std::uint8_t>::operator+=(const Grid<std::uint32_t>&);
template Grid<std::uint32_t>& Grid<std::uint32_t>::operator+=(const Grid<std::uint8_t>&);
