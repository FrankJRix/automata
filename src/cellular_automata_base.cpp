#include <automata/cellular_automata_base.h>
#include <automata/grid.h>
#include <automata/random_mt.h>

CellularAutomataBase::CellularAutomataBase(std::size_t width, std::size_t heigth, std::uint8_t radius)
	: m_grid(width, heigth)
	, m_old_grid(width, heigth)
	, m_radius{ radius }
{
	populate();
}

std::vector<Point> CellularAutomataBase::getNeighbors(std::size_t x, std::size_t y)
{
	std::vector<Point> list{};

	for(std::size_t i{1}; i <= m_radius; i++)
	{
		std::size_t ny{ y - i };
		std::size_t sy{ y + i };
		std::size_t wx{ x - i };
		std::size_t ex{ x + i }; 

		Point N{ x, ny };
		list.push_back(N);

		Point S{ x, sy };
		list.push_back(S);

		Point W{ wx, y };
		list.push_back(W);

		Point E{ ex, y };
		list.push_back(E);

		Point NW{ wx, ny };
		list.push_back(NW);

		Point NE{ ex, ny };
		list.push_back(NE);

		Point SW{ wx, sy };
		list.push_back(SW);

		Point SE{ ex, sy };
		list.push_back(SE);
	}

	return list;
}

void CellularAutomataBase::display()
{
	getMap()->display();
}

void CellularAutomataBase::savePNG()
{
	getMap()->savePNG();
}

void CellularAutomataBase::saveWeirdPNG()
{
	getMap()->saveWeirdPNG();
}

std::uint8_t CellularAutomataBase::countNeighbors(Point P)
{
	std::uint8_t count{};
	
	for(auto item: getNeighbors(P.x, P.y))
	{
		count += getValue(item.x, item.y);
	}
	return count;
}

void CellularAutomataBase::populate() // TODO: add varied distributions
{
	std::size_t w = getMap()->getWidth();
	std::size_t h = getMap()->getHeigth();

	for(std::size_t j{}; j < h; j++)
	{
		for(std::size_t i{}; i < w; i++)
		{
			std::uint8_t val{ static_cast<std::uint8_t>(Random::get(0,1)) };
			setValue(i, j, val);
		}
	}
	
	m_old_grid = m_grid;
}

std::uint8_t CellularAutomataBase::cellEvolutionMajority(std::size_t x, std::size_t y)
{
	std::uint8_t num{ countNeighbors(Point{x, y}) };
	std::uint8_t cell{};

	if(num >= (4 * m_radius + 1) ) cell = 1;

	return cell;
}

std::uint8_t CellularAutomataBase::cellEvolutionCaves(std::size_t x, std::size_t y)
{
	std::uint8_t num{ countNeighbors(Point{x, y}) };
	std::uint8_t cell{};

	if(num >= (4 * m_radius + 1) ) cell = 1;
	else if(num >= (4 * m_radius) ) cell = getValue(x, y);

	return cell;
}

void CellularAutomataBase::doEpochMajority()
{
	std::size_t w = getMap()->getWidth();
	std::size_t h = getMap()->getHeigth();
	Grid<std::uint8_t> temp(w, h);

	for(std::size_t j{}; j < h; j++)
	{
		for(std::size_t i{}; i < w; i++)
		{
			std::uint8_t c{ cellEvolutionMajority(i, j) };
			temp.setValue(i, j, c);
		}
	}
	
	m_old_grid = m_grid;
	m_grid = temp;
}

void CellularAutomataBase::doEpochCaves()
{
	std::size_t w = getMap()->getWidth();
	std::size_t h = getMap()->getHeigth();
	Grid<std::uint8_t> temp(w, h);

	for(std::size_t j{}; j < h; j++)
	{
		for(std::size_t i{}; i < w; i++)
		{
			std::uint8_t c{ cellEvolutionCaves(i, j) };
			temp.setValue(i, j, c);
		}
	}
	
	m_old_grid = m_grid;
	m_grid = temp;
}

void CellularAutomataBase::run(std::size_t epochs)
{
	int end{};
	//populate();

	for(std::size_t i{}; i < epochs; i++)
	{
		// display();
		doEpochCaves();

		end = i;

		if(*getMap() == *getOldMap()) 
		{
			break;
		};
	}

	std::cout << "\n\nFINAL RESULT at epoch " << end << "\n";
	// display();
}

Grid<std::uint8_t>* CellularAutomataBase::getMap()
{
	return &m_grid;
}

Grid<std::uint8_t>* CellularAutomataBase::getOldMap()
{
	return &m_old_grid;
}

std::uint8_t CellularAutomataBase::getValue(std::size_t x, std::size_t y)
{
	return getMap()->getValue(x, y);
}

void CellularAutomataBase::setValue(std::size_t x, std::size_t y, std::uint8_t value)
{
	getMap()->setValue(x, y, value);
}