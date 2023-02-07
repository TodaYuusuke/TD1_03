#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/Object.h"



class Enemy :public Object
{
public:
	// コンストラクタ
	Enemy(Point centerPosition, Point size, Object* _object);
	// デストラクタ
	~Enemy();

	// 初期化
	void SuccessorInitialize() override;
	// 更新
	void SuccessorUpdate() override;
	// 描画
	void Draw() override;
	// タイプ取得
	ObjectType GetType() override;

private:

	// -1 : 左
	//	1 : 右
	//  0 : 停止
	int direct;


	// プレイヤーの座標を参照
	Object* object;

};
