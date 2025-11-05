#include "Drawer.h"

Drawer::Drawer(int width, int height, int originX, int originY) {
	initgraph(width, height);
	setorigin(originX, originY);
	setbkcolor(WHITE);
	cleardevice();
}

Drawer::~Drawer() {
	closegraph();
}

//³õÆÚ¥á¥Ã¥·¥å¤òÃè¤¯
void Drawer::DrawInitialGrid(int cols, int rows) {
	setfillcolor(BLACK);
	
		for (int i = -1; i < rows; i++)
		{
			solidrectangle(-RODE / 2 - WALL, i * CELL_SIZE + RODE / 2 + 1, (cols - 1) * CELL_SIZE + RODE / 2 + WALL, i * CELL_SIZE + RODE / 2 + WALL);
		}
		for (int i = -1; i < cols; i++)
		{
			solidrectangle(i * CELL_SIZE + RODE / 2 + 1, -RODE / 2 - WALL, i * CELL_SIZE + RODE / 2 + WALL, (rows - 1) * CELL_SIZE + RODE / 2 + WALL);
		}
	
}

void Drawer::DrawCell(Cell* cell, COLORREF color) {
	int x = cell->x;
	int y = cell->y;
	setfillcolor(color);
	solidrectangle(x * CELL_SIZE - RODE / 2, y * CELL_SIZE - RODE / 2, x * CELL_SIZE + RODE / 2, y * CELL_SIZE + RODE / 2);

}

void Drawer::DrawConnection(Cell* a, Cell* b, COLORREF color) {
	int x1 = a->x, y1 = a->y;
	int x2 = b->x, y2 = b->y;
	setfillcolor(color);

	// ÏÂ¤Ë¤¢¤ë
	if (x1 == x2 && y1 > y2) 
		solidrectangle(x1 * CELL_SIZE - RODE / 2, y1 * CELL_SIZE - RODE / 2 - WALL, x1 * CELL_SIZE + RODE / 2, y1 * CELL_SIZE - RODE / 2);
	// ÉÏ¤Ë¤¢¤ë
	else if (x1 == x2 && y1 < y2) 
		solidrectangle(x1 * CELL_SIZE - RODE / 2, y1 * CELL_SIZE + RODE / 2, x1 * CELL_SIZE + RODE / 2, y1 * CELL_SIZE + RODE / 2 + WALL);
	// ÓÒ‚È¤Ë¤¢¤ë
	else if (y1 == y2 && x1 > x2) 
		solidrectangle(x1 * CELL_SIZE - RODE / 2 - WALL, y1 * CELL_SIZE - RODE / 2, x1 * CELL_SIZE - RODE / 2, y1 * CELL_SIZE + RODE / 2);
	//×ó‚È¤Ë¤¢¤ë
	else if (y1 == y2 && x1 < x2) 
		solidrectangle(x1 * CELL_SIZE + RODE / 2, y1 * CELL_SIZE - RODE / 2, x1 * CELL_SIZE + RODE / 2 + WALL, y1 * CELL_SIZE + RODE / 2);
}
