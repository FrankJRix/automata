#include <automata/cellular_automata_base.h>
#include <automata/grid.h>
#include <automata/random_mt.h>

CellularAutomataBase::CellularAutomataBase(int width, int heigth, int radius)
	: m_grid(width, heigth)
	, m_old_grid(width, heigth)
	, m_radius{ radius }
{
}

std::vector<Point> CellularAutomataBase::getNeighbors(int x, int y)
{
	std::vector<Point> list{};

	for(int i{1}; i <= m_radius; i++)
	{
		int ny{ y - i };
		int sy{ y + i };
		int wx{ x - i };
		int ex{ x + i }; 

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

	if(num >= (4 * m_radius + 1) ) cell = 1;
	else if(num >= (4 * m_radius) ) cell = getValue(x, y);

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
	int end{};
	populate();

	for(int i{}; i < epochs; i++)
	{
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