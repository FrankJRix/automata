#ifndef CELLULAR_AUTOMATA_BASE_H
#define CELLULAR_AUTOMATA_BASE_H

#include <automata/random_mt.h>
#include <automata/grid.h>
#include <vector>
#include <iostream>

#define BIRTH_THRESH 5
#define SAME_THRESH 4
#define MAX_EPOCHS 100
#define DEFAULT_RADIUS 1


/*
allora, per 
	r=1 -> N=5, N-1=4
	r=2 -> N=9, N-1=8
	r=3 -> N=13, N-1=12
	r=4 -> N=17, N-1=16
	r=5 -> N=21, N-1=20

quindi N = 4r + 1
*/


struct Point
{
	std::size_t x;
	std::size_t y;
};

class CellularAutomataBase
{
protected:
	Grid<std::uint8_t> m_grid;
	Grid<std::uint8_t> m_old_grid;
	std::uint8_t m_radius;
	
	// helper methods
	std::vector<Point> getNeighbors(std::size_t x, std::size_t y);
	std::uint8_t countNeighbors(Point P);
	std::uint8_t cellEvolutionMajority(std::size_t x, std::size_t y);
	std::uint8_t cellEvolutionCaves(std::size_t x, std::size_t y);

public:
	CellularAutomataBase(std::size_t width, std::size_t heigth, std::uint8_t radius = DEFAULT_RADIUS);
	//virtual ~CellularAutomataBase() = default;

	void display();
	void savePNG();
	void saveWeirdPNG();

	void populate();
	void doEpochMajority();
	void doEpochCaves();
	virtual void run(std::size_t epochs = MAX_EPOCHS);

	// setters and getters
	Grid<std::uint8_t>* getMap();
	Grid<std::uint8_t>* getOldMap();
	std::uint8_t getValue(std::size_t x, std::size_t y);
	void setValue(std::size_t x, std::size_t y, std::uint8_t value);
	
};

#endif