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
	// ジャンプ
	void Jump();
	// ワイヤー関連
	void ShotWire();


	// 当たり判定

	// 上下左右の当たり判定の関数
	void CheckHitBoxRhombus();
	// 左上、左下、右上、右下の当たり判定の関数
	void CheckHitBoxQuad();



private: // メンバ変数

	

	// 状態フラグ

	// 空中にいるか（地面についてないか）
	bool isFlying;

	// 照準の座標
	Point reticlePosition;


	// ワイヤー管理クラス
	WireManager* wireManager;

};