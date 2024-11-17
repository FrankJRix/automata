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
	int x;
	int y;
};

class CellularAutomataBase
{
protected:
	Grid m_grid;
	Grid m_old_grid;
	int m_radius;
	
public:
	CellularAutomataBase(int width, int heigth, int radius = DEFAULT_RADIUS);
	std::vector<Point> getNeighbors(int x, int y);
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