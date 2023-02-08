#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/Object.h"

#include "Class/AttackHitBox/EnemyAttackHitBox.h"

class IronBalloon :public Object
{
public:
	// コンストラクタ
	IronBalloon(Point centerPosition, Point size, Object* _object);
	// デストラクタ
	~IronBalloon();

	// 初期化
	void SuccessorInitialize() override;
	// 更新
	void SuccessorUpdate() override;
	// 描画
	void Draw() override;
	// タイプ取得
	ObjectType GetType() override;

private:

	// 経過フレーム
	int elapsedFrame;

	// -1 : 左
	//	1 : 右
	//  0 : 停止
	int direct;

	// 上下のフワフワ感
	float degree;

	// プレイヤーの座標を参照
	Object* object;

};
