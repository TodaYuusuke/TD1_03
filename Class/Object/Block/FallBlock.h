#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/Object.h"

// ワイヤーが刺さるブロック

class Block :
	public Object {
public: // メンバ関数

	// コンストラクタ
	Block(Point centerPosition, Point size);
	// デストラクタ
	~Block();

	// 初期化
	void SuccessorInitialize() override;
	// 更新
	void SuccessorUpdate() override;
	// 描画
	void Draw() override;
	// タイプ取得
	ObjectType GetType() override;

private: // メンバ変数

	// 生成されてから、消えるまでの時間
	int vanishFlame;
};