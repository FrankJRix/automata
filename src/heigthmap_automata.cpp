#include <automata/heigthmap_automata.h>

HeigthmapAutomata::HeigthmapAutomata(std::size_t width, std::size_t heigth, std::uint8_t radius)
	: CellularAutomataBase(width, heigth, radius)
	, m_heigthmap(width, heigth)
{
}

void HeigthmapAutomata::run(std::size_t epochs)
{
	int end{};
	populate();

	for(std::size_t i{1}; i <= epochs; i++)
	{
		// display();
		doEpochMajority();
		m_heigthmap += *getMap();

		end = i;

		if(*getMap() == *getOldMap()) 
		{
			break;
		};
	}

	m_heigthmap.savePNG(end);

	std::cout << "\n\nFINAL RESULT at epoch " << end << "\n";
}
