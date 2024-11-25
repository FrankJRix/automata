#include <automata/grid.h>
#include <automata/lodepng.h>
#include <iostream>
#include <algorithm>

#define WEIRDNESS 1

template<typename T>
Grid<T>::Grid(std::size_t width, std::size_t height)
	: m_width{width}
	, m_height{height}
	, m_data(width * height)
{
}

template<typename T>
T Grid<T>::getValue(std::size_t x, std::size_t y)
{
	x = ((x % m_width) + m_width) % m_width;
	y = ((y % m_height) + m_height) % m_height;
	return m_data[x + y * m_width];
}

template<typename T>
void Grid<T>::setValue(std::size_t x, std::size_t y, T value)
{
	x = ((x % m_width) + m_width) % m_width;
	y = ((y % m_height) + m_height) % m_height;
	m_data[x + y * m_width] = value;
}

template<typename T>
std::size_t Grid<T>::getWidth()
{
	return m_width;
}

template<typename T>
std::size_t Grid<T>::getHeight()
{
	return m_height;
}

template<typename T>
void Grid<T>::display()
{
	for(int j{ 0 }; j < m_height; j++)
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
void Grid<T>::savePNG()
{
	std::vector<unsigned char> temp;
	temp.resize(m_width * m_height);

	for(int j{ 0 }; j < m_height; j++)
	{
		for(int i{ 0 }; i < m_width; i++)
		{
			std::size_t coord{ i + j * m_width };
			temp[coord] = static_cast<unsigned char>(getValue(i, j) * 255);
		}
	}
	
	unsigned error = lodepng::encode("output/out.png", temp, m_width, m_height, LCT_GREY);
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

template<typename T>
void Grid<T>::saveWeirdPNG()
{
	std::vector<unsigned char> temp;
	temp.resize(m_width * m_height * 3);

	for(int j{ 0 }; j < m_height; j++)
	{
		for(int i{ 0 }; i < m_width; i++)
		{
			std::size_t coord{ 3 * i + 3 * j * m_width };

			T rgb_r{ getValue(i + WEIRDNESS * 2, j) };
			T rgb_g{ getValue(i, j + WEIRDNESS * 2) };
			T rgb_b{ getValue(i - WEIRDNESS, j - WEIRDNESS) };

			temp[coord + 0] = static_cast<unsigned char>(rgb_r * 255);
			temp[coord + 1] = static_cast<unsigned char>(rgb_g * 255);
			temp[coord + 2] = static_cast<unsigned char>(rgb_b * 255);
		}
	}
	
	unsigned error = lodepng::encode("output/outW.png", temp, m_width, m_height, LCT_RGB);
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
template class Grid<double>;

// uint8
template Grid<std::uint8_t>& Grid<std::uint8_t>::operator+=(const Grid<std::uint8_t>&);
// uint32
template Grid<std::uint32_t>& Grid<std::uint32_t>::operator+=(const Grid<std::uint32_t>&);
// double
template Grid<double>& Grid<double>::operator+=(const Grid<double>&);

// 8 + 32
template Grid<std::uint8_t>& Grid<std::uint8_t>::operator+=(const Grid<std::uint32_t>&);
// 32 + 8
template Grid<std::uint32_t>& Grid<std::uint32_t>::operator+=(const Grid<std::uint8_t>&);
// double + 8
template Grid<double>& Grid<double>::operator+=(const Grid<std::uint8_t>&);
