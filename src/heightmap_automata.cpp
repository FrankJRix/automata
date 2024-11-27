#include <automata/heightmap_automata.h>

HeightmapAutomata::HeightmapAutomata(std::size_t width, std::size_t height, std::uint8_t radius)
	: CellularAutomataBase(width, height, radius)
	, m_heightmap(width, height)
{
}

void HeightmapAutomata::run(std::size_t epochs)
{
	int end{};
	populate();

	for(std::size_t i{1}; i <= epochs; i++)
	{
		// display();
		doEpochCaves();
		m_heightmap += *getMap();

		end = i;

		if(*getMap() == *getOldMap()) 
		{
			break;
		};
	}

	m_heightmap /= end;
	m_heightmap.savePNG();

	std::cout << "\n\nFINAL RESULT at epoch " << end << "\n";
}

void HeightmapAutomata::averageHeight(Point P, std::uint8_t r)
{
	double sum{};
	int count{};
	
	for(auto item: getNeighbors(P.x, P.y, r))
	{
		sum += m_heightmap.getValue(item.x, item.y);
		count++;
	}

	m_heightmap.setValue(P.x, P.y, sum / count);
}

void HeightmapAutomata::smoothenMap(std::uint8_t r)
{
	std::size_t w = getMap()->getWidth();
	std::size_t h = getMap()->getHeight();

	for(std::size_t j{}; j < h; j++)
	{
		for(std::size_t i{}; i < w; i++)
		{
			averageHeight(Point{i, j}, r);
		}
	}

	m_heightmap.savePNG();
}
