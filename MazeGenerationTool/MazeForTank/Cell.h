#pragma once
#include <vector>
#include <limits>


/// <summary>
/// これは迷路を生成するためのセルクラスの実装です。
/// </summary>


enum class E_CellState {
	Unvisited,
	Visited,
};


class Cell
{
public:
	int x, y;//位置
	E_CellState cellState;
	std::vector<Cell*> neighbors;//隣接するセル

	Cell(int colum = 0, int row = 0) {
		x = colum;
		y = row;
		cellState = E_CellState::Unvisited;
	}

	
	void Connect(Cell* other) {
		neighbors.push_back(other);
		other->neighbors.push_back(this);
	}

};

