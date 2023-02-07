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
	Player(Point centerPosition, WireManager* _wireManager);
	// デストラクタ
	~Player();

	// 初期化
	void SuccessorInitialize() override;
	// 更新
	void Update() override;
	// 更新
	void SuccessorUpdate() override;
	// 描画
	void Draw() override;

	// タイプ取得
	ObjectType GetType() override;

	// 移動制限
	bool GetIsLimitMove() { return isLimitMove; };
	// 移動制限左上
	Point GetLimitLeftTop() { return limitLeftTop; };
	// 移動制限右下
	Point GetLimitRightBottom() { return limitRightBottom; };


	// 移動制限
	void SetIsLimitMove(bool a) { isLimitMove = a; };
	// 移動制限左上
	void SetLimitLeftTop(Point p) { limitLeftTop = p; };
	// 移動制限右下
	void SetLimitRightBottom(Point p) { limitRightBottom = p; };

private: // 関数


	// どちらもUpdate()で毎フレーム呼び出すこと

	// 移動関連
	void Move();
	// 照準移動
	void ReticleMove();
	// ジャンプ
	void Jump();
	// ワイヤー関連
	void ShotWire();

	// 移動制限関数
	void LimitMovement();

	// リスポーン関数
	void Respawn();

	// アニメーション
	void Animation();


	// 当たり判定をオーバーライド

	// オブジェクト自体の当たり判定をチェックする関数
	void CheckFieldHitBox() override;

private: // メンバ変数

	// 状態フラグ

	// 照準の座標
	Point reticlePosition;
	// 前の照準の座標
	Point preReticlePosition;
	// 前のフレームのマウス座標
	Point preMousePosition;


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

	// プレイヤーの移動制限
	bool isLimitMove;

	// 制限する左上座標
	Point limitLeftTop;
	// 制限する右下座標
	Point limitRightBottom;

	// アニメーション
	// 今の状態
	int state;
	// 前の状態
	int preState;
	// 状態が変わってからの状態
	int buffState;

	// 状態が変わってからのフレーム数
	int stateChengeFlame;

	// アニメーション用フレームカウント
	int animationFlameCount;

	// 今のアニメーションフレーム
	int animationFlame;


	// リスポーン地点
	Point resqawnPosition;

	// リスポーン用前フレーム座標
	Point preCenterPosition;

	// isFlying がfalseになった瞬間の感知
	bool preIsFlying;

	// リスポーンするか
	bool isRespawn;

};