#pragma once
#include "MyBase/MyBase.h"
#include "Class/PublicFlag/PublicFlag.h"

enum MapChipType {
	// 空白（何もない）
	kTypeAir,
	// 通常マス
	kTypeNormal,
	// 背景マス（当たり判定無し）
	kTypeWall,
	// 壊れるマス
	kTypeWeak,
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
	/// <param name="isBlock ヒットするのがBlockかどうか"></param>
	/// <returns></returns>
	bool CheckHitBox(Point hitPosition, bool isBlock);

	// パブリック変数
	MapChipType type;
};