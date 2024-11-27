#ifndef HEIGHTMAP_AUTOMATA_H
#define HEIGHTMAP_AUTOMATA_H
#include <automata/cellular_automata_base.h>

class HeightmapAutomata : public CellularAutomataBase
{
private:
	Grid<double> m_heightmap;
	std::size_t m_end;

public:
	HeightmapAutomata(std::size_t width, std::size_t height, std::uint8_t radius = DEFAULT_RADIUS);
	void run(std::size_t epochs = MAX_EPOCHS) override;
	void averageHeight(Point P, std::uint8_t r);
	void smoothenMap(std::uint8_t r);

};

#endif