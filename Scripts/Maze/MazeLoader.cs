using UnityEngine;
using System.IO;

/// <summary>
/// JSON形式の迷路データを読み込み、3D迷路を生成するクラス
/// </summary>
public class MazeLoader : MonoBehaviour
{
	[Header("Assets")]
	public TextAsset jsonFile; 
	public GameObject wallPrefab; 
	public GameObject floorPrefab; 
	public GameObject enemyPrefab; 
	
	[Header("Settings")]
	public float spacing = 2.0f; // セルのサイズ
	
	
	public void GenerateMaze()
	{
		// 古い迷路をクリア
		ClearMaze();

		if (jsonFile == null)
		{
			
			return;
		}

		// JSONを解析
		MazeData mazeData = JsonUtility.FromJson<MazeData>(jsonFile.text);
		
		// すべての迷路パーツを格納する親オブジェクトを作成
		GameObject mazeParent = new GameObject("GeneratedMaze");
		mazeParent.transform.SetParent(this.transform);
	
		foreach (CellData cell in mazeData.cells)
		{

			Vector3 cellPos = new Vector3(cell.x * spacing, 0, -cell.y * spacing);
			
			// 床を配置
			if(floorPrefab != null) 
				Instantiate(floorPrefab, cellPos, Quaternion.identity, mazeParent.transform);

			// 上側の壁を配置
			if (cell.hasTopWall)
			{
				Vector3 wallPos = cellPos + new Vector3(0, 0, 0.5f * spacing);
				Instantiate(wallPrefab, wallPos, Quaternion.identity, mazeParent.transform);
			}

			// 左側の壁を配置
			if (cell.hasLeftWall)
			{
				Vector3 wallPos = cellPos + new Vector3(-0.5f * spacing, 0, 0);
				Instantiate(wallPrefab, wallPos, Quaternion.Euler(0, 90, 0), mazeParent.transform);
			}
			
			// 敵を配置
			if (cell.hasEnemy && enemyPrefab != null) 
				Instantiate(enemyPrefab, cellPos, Quaternion.identity, mazeParent.transform);

			// 最右端の壁
			if (cell.x == mazeData.width - 1)
			{
				Vector3 wallPos = cellPos + new Vector3(0.5f * spacing, 0, 0);
				Instantiate(wallPrefab, wallPos, Quaternion.Euler(0, 90, 0), mazeParent.transform);
			}
			
			// 最下端の壁
			if (cell.y == mazeData.height - 1)
			{
				Vector3 wallPos = cellPos + new Vector3(0, 0, -0.5f * spacing);
				Instantiate(wallPrefab, wallPos, Quaternion.identity, mazeParent.transform);
			}
		}
		
	}

	// クリア用
	public void ClearMaze()
	{
		
		// MazeManagerに付属するすべての子オブジェクトを削除
		while (transform.childCount > 0)
		{
			
			DestroyImmediate(transform.GetChild(0).gameObject);
		}
		Debug.Log("Cleared old maze.");
	}
}