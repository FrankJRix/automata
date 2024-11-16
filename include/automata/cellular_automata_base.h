#ifndef CELLULAR_AUTOMATA_BASE_H
#define CELLULAR_AUTOMATA_BASE_H

#include <automata/random_mt.h>
#include <automata/grid.h>
#include <array>
#include <iostream>

#define BIRTH_THRESH 5
#define SAME_THRESH 4
#define MAX_EPOCHS 100

struct Point
{
	int x;
	int y;
};

class CellularAutomataBase
{
protected:
	Grid m_grid;
	Grid m_old_grid;
	
public:
	CellularAutomataBase(int width, int heigth);
	std::array<Point, 8> getNeighbors(int x, int y);
	void display();
	void savePNG();
	void saveWeirdPNG();

	int countNeighbors(Point P);
	void populate();
	int cellEvolution(int x, int y);
	void doEpoch();
	void run(int epochs = MAX_EPOCHS);

	// setters and getters
	Grid* getMap();
	Grid *getOldMap();
	int getValue(int x, int y);
	void setValue(int x, int y, int value);
	
};

#endif