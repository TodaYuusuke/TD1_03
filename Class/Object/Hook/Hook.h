#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/Object.h"

// ワイヤーが刺さる場所

class Hook :
	public Object {
public: // メンバ関数

	// コンストラクタ
	Hook(Point centerPosition, Point size);
	// デストラクタ
	~Hook();

	// 初期化
	void SuccessorInitialize() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;
	// タイプ取得
	ObjectType GetType() override;

	// 当たり判定関連

	// オブジェクトに対する当たり判定をチェックする関数
	// 返り値：ヒットしていた場合 ... true
	// 引数：チェックするPoint
	bool CheckHitBox(Point hitPosition) override;

private:

	int pullCount;

};