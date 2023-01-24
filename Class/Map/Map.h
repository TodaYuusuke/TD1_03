#pragma once
#include "MyBase/MyBase.h"

enum MapChipType {
	// 空白（何もない）
	kTypeAir,
	// 通常マス
	kTypeNormal,
};

class Map {
public: // メンバ関数

	// コンストラクタ
	Map();
	// デストラクタ
	~Map();

	// 初期化
	void Initialize(MapChipType type);
	// 更新
	void Update();
	// 描画
	void Draw(Point drawPosition, int drawImageNum);

	/// <summary>
	/// 指定した座標がマップにヒットしているかどうか
	/// </summary>
	/// <param name="hitPosition 当たり判定を確認する座標"></param>
	/// <returns></returns>
	bool CheckHitBox(Point hitPosition);

	// パブリック変数
	MapChipType type;
};