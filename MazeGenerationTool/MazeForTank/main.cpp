#include "Maze.h"

// ここで迷路のサイズを設定
const int MAP_COLS = 30;
const int MAP_ROWS = 30;
const int ENEMY_COUNT = 5;
int main()
{
	//Maze オブジェクトを作成
	Maze maze(MAP_COLS, MAP_ROWS);
	//実行
	maze.run();
	//一時停止（続行するには Enter キーを押してください）
	system("pause");
	return 0;
}