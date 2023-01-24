#pragma once
#include "MyBase/Include/MyBase.h"
#include "Class/Include/Object/Object.h"

// ワイヤーが刺さるオブジェクト

class Hook : public Object
{
public:

	// コンストラクタ
	Hook(Point centerPosition, Point size);
	/// デストラクタ
	~Hook();

	// 初期化
	void SuccessorInitialize() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;
	// タイプ取得
	ObjectType GetType() override;

};

