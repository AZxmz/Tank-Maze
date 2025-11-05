#pragma once
#include <vector>
#include <stack>
#include "Cell.h"
#include "Drawer.h"

//メインウィンドウのサイズ
const int Window_Width = 1200;
const int Window_Height = 800;


/// <summary>
/// これは迷路のコアクラスです。
/// </summary>
class Maze
{
public:
	Maze(int cols, int rows);
	~Maze();
	void run();

private:
	int m_cols, m_rows;
	Cell* m_startNode;
	Cell* m_endNode;

	std::vector<std::vector<Cell*>> m_grid;

	//描画ツール
	Drawer m_drawer;

	//迷路生成
	void GenerateMaze();

	std::vector<Cell*> getGridNeighbors(Cell* cell, E_CellState state);

};

