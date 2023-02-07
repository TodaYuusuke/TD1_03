#pragma once
#include "MyBase/MyBase.h"
#include "Class/SceneManager/Scene/BaseScene.h"

class BossStage :
	public BaseScene{
public: // メンバ関数

	// コンストラクタ
	BossStage();
	// デストラクタ
	~BossStage();

	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private: // メンバ関数

	// ゲームオーバー時の処理
	void GameOverUpdate();
	// ゲームオーバー時の処理
	void GameOverDraw();


private: // メンバ変数

	ObjectManager objectManager;
	WireManager wireManager;
	Boss boss;

	// ゲームオーバーかどうか
	bool isGameOver;
	// ゲームオーバー時の背景
	int gameOverColor;
	// 中心から大きくなるための変数
	// 0 ～ 1
	float gameOverT;
};