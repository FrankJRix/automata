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
