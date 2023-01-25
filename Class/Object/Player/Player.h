#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/Object.h"

#include "Class/Wire/WireManager.h"

#include "Class/AttackHitBox/EnemyAttackHitBox.h"

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

	// 当たり判定をオーバーライド
	
	// オブジェクト自体の当たり判定をチェックする関数
	void CheckFieldHitBox() override;

private: // メンバ変数

	// 状態フラグ

	// 照準の座標
	Point reticlePosition;


	// ワイヤー管理クラス
	WireManager* wireManager;

	// ヒット後の無敵時間
	int invincibleFrame;
	// 現在右を向いているかどうか
	bool isRight;

	// カメラを移動させるための t
	float screenT;

	//////////////
	/// HP関連 ///
	//////////////
	
	// 言わずもがな
	int HP;
	// HP を表示するかどうか
	bool isDrawHP;
	// HP を表示するフレーム数
	int drawHPFrame;



	//////////////
	///ここまで///
	//////////////




};