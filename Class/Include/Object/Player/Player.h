#pragma once
#include "MyBase/Include/MyBase.h"
#include "Class/Include/Object/Object.h"

#include "Class/Include/Wire/WireManager.h"


// いうまでもなくプレイヤー
class WireManager;

class Player :
	public Object {
public: // メンバ関数

	// コンストラクタ
	Player(Point centerPosition,WireManager* _wireManager);
	// デストラクタ
	~Player();

	// 初期化
	void SuccessorInitialize() override;
	// 更新
	void SuccessorUpdate() override;
	// 描画
	void Draw() override;

	// タイプ取得
	ObjectType GetType() override;


private: // 関数

	// どちらもUpdate()で毎フレーム呼び出すこと

	// 移動関連
	void Move();
	// ワイヤーを射出する動作
	void ShotWire();

private: // メンバ変数


	// マウス座標
	Point ReticlePosition;

	WireManager* wireManager;

};