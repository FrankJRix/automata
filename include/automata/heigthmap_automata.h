#ifndef HEIGTHMAP_AUTOMATA_H
#define HEIGTHMAP_AUTOMATA_H
#include <automata/cellular_automata_base.h>

class HeigthmapAutomata : public CellularAutomataBase
{
private:
	Grid<std::uint8_t> m_heigthmap;
	std::size_t m_end;

public:
	HeigthmapAutomata(std::size_t width, std::size_t heigth, std::uint8_t radius = DEFAULT_RADIUS);
	void run(std::size_t epochs = MAX_EPOCHS) override;

};

#endif