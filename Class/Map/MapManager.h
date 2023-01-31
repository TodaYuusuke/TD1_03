#pragma once
#include "MyBase/MyBase.h"

#include "Class/Map/Map.h"

// マップを管理するクラス

// マップの読み込みの仕様上、このクラス内の処理はすべてスクリーン座標で行う、外に出す場合は必ずワールド座標で返すこと

class MapManager {
public: // メンバ関数

	// コンストラクタ
	MapManager();
	// デストラクタ
	~MapManager();


	// 初期化
	static void Initialize();
	// 更新
	static void Update();
	// 描画
	static void Draw();

	/// <summary>
	/// 指定した座標がマップにヒットしているかどうか
	/// </summary>
	/// <param name="hitPosition 当たり判定を確認する座標"></param>
	/// <returns>ヒットしていた場合 ... true、ヒットしていなかった場合 ... false</returns>
	static bool CheckHitBox(Point hitPosition);

private: // 関数

	// マップチップの形を決定する関数
	static int GetMapChipType(int y, int x);

private: // メンバ変数

	// マップの配列
	static Map map[BaseConst::kBossStageSizeHeight][BaseConst::kBossStageSizeWidth];
};