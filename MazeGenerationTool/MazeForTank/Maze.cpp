#include "Maze.h"
#include <ctime>
#include <iostream>
#include "JsonExporter.h"

Maze::Maze(int cols, int rows)
	: m_cols(cols), m_rows(rows),
	m_drawer(Window_Width, Window_Height, 20, 20)
{
	srand((unsigned)time(NULL));
	// すべてのセルをインスタンス化する
	m_grid.resize(m_cols);
	for (int i = 0; i < m_cols; i++)
	{
		m_grid[i].resize(m_rows);
		for (int j = 0; j < m_rows; j++)
		{
			m_grid[i][j] = new Cell(i, j);
		}
	}
	m_startNode = m_grid[0][0];
	m_endNode = m_grid[m_cols - 1][m_rows - 1];
}

Maze::~Maze()
{
	for (int i = 0; i < m_cols; i++)
	{
		for (int j = 0; j < m_rows; j++)
		{
			delete m_grid[i][j];
		}
	}

}

void Maze::run()
{
	//初期化
	m_drawer.DrawInitialGrid(m_cols, m_rows);

	//迷路を作成
	GenerateMaze(); 
	
	//迷路を観察するために一時停止
	system("pause");

	// 迷路データをJSON形式でエクスポート
	JsonExporter::exportToJSON(m_grid, m_cols, m_rows, "maze_data.json");

}

std::vector<Cell*> Maze::getGridNeighbors(Cell* cell, E_CellState state)
{
	std::vector<Cell*> neighbors;
	int x = cell->x; int y = cell->y;

	// 指定された状態について近隣をチェック
	if (y > 0 && m_grid[x][y - 1]->cellState == state)
		neighbors.push_back(m_grid[x][y - 1]);
	if (y < m_rows - 1 && m_grid[x][y + 1]->cellState == state)
		neighbors.push_back(m_grid[x][y + 1]);
	if (x > 0 && m_grid[x - 1][y]->cellState == state)
		neighbors.push_back(m_grid[x - 1][y]);
	if (x < m_cols - 1 && m_grid[x + 1][y]->cellState == state)
		neighbors.push_back(m_grid[x + 1][y]);

	return neighbors;
}


// --- 迷路生成 (Prim アルゴリズム) ---
void Maze::GenerateMaze()
{
	//  "境界" リスト 
	std::vector<Cell*> frontier;
	//  スタート地点から開始
	m_startNode->cellState = E_CellState::Visited; // "迷路内" としてマーク
	//  スタート地点の "UNVISITED" 隣接セルを取得
	std::vector<Cell*> startNeighbors = getGridNeighbors(m_startNode, E_CellState::Unvisited);
	for (Cell* neighbor : startNeighbors)
	{
		frontier.push_back(neighbor);
	}
	// 境界リストが空になるまでループ
	while (!frontier.empty())
	{
		Sleep(1); // 視覚化を維持
		//境界リストから ランダムに*セルを1つ選択
		int index = rand() % frontier.size();
		Cell* current = frontier[index];
		//末尾要素と交換してポップ
		frontier[index] = frontier.back();
		frontier.pop_back();
		//迷路内としてマーク
		current->cellState = E_CellState::Visited;
		//このセルのすでに迷路内にある隣接セルを検索
		std::vector<Cell*> visitedNeighbors = getGridNeighbors(current, E_CellState::Visited);
		if (!visitedNeighbors.empty())
		{
			//迷路内にある隣接セルからランダムに1つ選択
			Cell* neighbor = visitedNeighbors[rand() % visitedNeighbors.size()];
			//壁を壊して接続
			m_drawer.DrawConnection(current, neighbor, WHITE);
			current->Connect(neighbor);
		}
		
		std::vector<Cell*> newNeighbors = getGridNeighbors(current, E_CellState::Unvisited);
		for (Cell* neighbor : newNeighbors)
		{
			// 境界内としてマークし、リストに追加
			neighbor->cellState = E_CellState::Visited;
			frontier.push_back(neighbor);
		}
	}
}