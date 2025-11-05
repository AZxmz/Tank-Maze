using UnityEngine;

/// <summary>
/// 从Json转换数据
/// </summary>

[System.Serializable]
public class CellData
{
	
	public int x;
	public int y;
	public bool hasEnemy;
	public bool hasTopWall;
	public bool hasLeftWall;
}

[System.Serializable]
public class MazeData
{
	
	public int width;
	public int height;
	public CellData[] cells;
}