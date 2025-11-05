#pragma once
#include <string>
#include <vector>
#include "Cell.h" // 需要 Cell 的完整定义

class JsonExporter
{
private:
	// 辅助函数：检查一个单元格是否与特定坐标的邻居相连
	static bool hasConnection(Cell* cell, int targetX, int targetY);

public:

	static void exportToJSON(const std::vector<std::vector<Cell*>>& grid, int cols, int rows, const std::string& filename);
};