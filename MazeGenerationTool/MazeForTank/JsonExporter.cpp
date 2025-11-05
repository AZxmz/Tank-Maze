#include "JsonExporter.h"
#include "json.hpp" //必要な追加ライブラリ
#include <fstream>
#include <iostream>


using json = nlohmann::json;

//接続をチェックする
bool JsonExporter::hasConnection(Cell* cell, int targetX, int targetY)
{
	for (Cell* neighbor : cell->neighbors)
	{
		if (neighbor->x == targetX && neighbor->y == targetY)
		{
			return true;
		}
	}
	return false;
}


void JsonExporter::exportToJSON(const std::vector<std::vector<Cell*>>& grid, int cols, int rows, const std::string& filename)
{
	std::cout << "Starting JSON export..." << std::endl;

	//ルート JSON オブジェクトを作成
	json root;
	root["width"] = cols;
	root["height"] = rows;

	//すべてのセルを格納する JSON 配列を作成
	json cellArray = json::array();

	//すべてのセルを走査
	for (int j = 0; j < rows; ++j)
	{
		for (int i = 0; i < cols; ++i)
		{
			Cell* current = grid[i][j];
			json cellData;

			cellData["x"] = current->x;
			cellData["y"] = current->y;
			

			
			// // 0行目の場合は必ず壁あり；それ以外は、(i, j-1) と接続されているかをチェック
			cellData["hasTopWall"] = (j > 0) ? !hasConnection(current, i, j - 1) : true;

			
			//0列目の場合は必ず壁あり；それ以外は、(i-1, j) と接続されているかをチェック
			cellData["hasLeftWall"] = (i > 0) ? !hasConnection(current, i - 1, j) : true;

			
			cellArray.push_back(cellData);
		}
	}

	
	root["cells"] = cellArray;

	// JSON オブジェクトをファイルに書き込み
	try
	{
		std::ofstream file(filename);
		file << root.dump(4); 
		file.close();
		std::cout << "Successfully exported maze to " << filename << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error writing JSON file: " << e.what() << std::endl;
	}
}