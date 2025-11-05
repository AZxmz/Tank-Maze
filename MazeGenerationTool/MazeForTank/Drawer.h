#pragma once
#include <graphics.h>
#include <string>
#include "Cell.h" 

/// <summary>
/// √‘¬∑§Œ“ï“ôªØ√Ëª≠•Ø•È•π§«§π°£
/// </summary>
class Drawer
{
public:
	
	static const int RODE = 9; 
	static const int WALL = 3; 
	static const int CELL_SIZE = RODE + WALL;

	Drawer(int width, int height, int originX, int originY);
	~Drawer();

	void DrawInitialGrid(int cols, int rows);
	void DrawCell(Cell* cell, COLORREF color);
	void DrawConnection(Cell* a, Cell* b, COLORREF color);
};


