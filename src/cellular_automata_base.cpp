#include <automata/cellular_automata_base.h>
#include <automata/grid.h>
#include <automata/random_mt.h>

CellularAutomataBase::CellularAutomataBase(int width, int heigth)
	: m_grid(width, heigth)
	, m_old_grid(width, heigth)
{
}

std::array<Point, 8> CellularAutomataBase::getNeighbors(int x, int y)
{
	int ny{ y-1 };
	int sy{ y+1 };
	int wx{ x-1 };
	int ex{ x+1 }; 

	Point N{ x, ny };
	Point S{ x, sy };
	Point W{ wx, y };
	Point E{ ex, y };

	Point NW{ wx, ny };
	Point NE{ ex, ny };
	Point SW{ wx, sy };
	Point SE{ ex, sy };

	std::array<Point, 8> list{N, S, W, E, NW, NE, SW, SE};

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

int CellularAutomataBase::countNeighbors(Point P)
{
	int count{};
	
	for(auto item: getNeighbors(P.x, P.y))
	{
		count += getValue(item.x, item.y);
	}
	return count;
}

void CellularAutomataBase::populate()
{
	int w = getMap()->getWidth();
	int h = getMap()->getHeigth();

	for(int j{}; j < h; j++)
	{
		for(int i{}; i < w; i++)
		{
			int val{ Random::get(0,1) };
			setValue(i, j, val);
		}
	}
	
	m_old_grid = m_grid;
}

int CellularAutomataBase::cellEvolution(int x, int y)
{
	int num{ countNeighbors(Point{x, y}) };
	int cell{};

	if(num >= BIRTH_THRESH) cell = 1;
	else if(num >= SAME_THRESH) cell = getValue(x, y);

	return cell;
}

void CellularAutomataBase::doEpoch()
{
	int w = getMap()->getWidth();
	int h = getMap()->getHeigth();
	Grid temp(w, h);

	for(int j{}; j < h; j++)
	{
		for(int i{}; i < w; i++)
		{
			int c{ cellEvolution(i, j) };
			temp.setValue(i, j, c);
		}
	}
	
	m_old_grid = m_grid;
	m_grid = temp;
}

void CellularAutomataBase::run(int epochs)
{
	int hasChanged{};
	int end{};
	populate();

	for(int i{}; i < epochs; i++)
	{
		hasChanged = 0;

		// display();
		doEpoch();

		end = i;

		if(*getMap() == *getOldMap()) 
		{
			break;
		};
	}

	std::cout << "\n\nFINAL RESULT at epoch " << end << "\n";
	// display();
}

Grid* CellularAutomataBase::getMap()
{
	return &m_grid;
}

Grid* CellularAutomataBase::getOldMap()
{
	return &m_old_grid;
}

int CellularAutomataBase::getValue(int x, int y)
{
	return getMap()->getValue(x, y);
}

void CellularAutomataBase::setValue(int x, int y, int value)
{
	getMap()->setValue(x, y, value);
}