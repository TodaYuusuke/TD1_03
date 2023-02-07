#pragma once
#include "MyBase/MyBase.h"
#include "Class/SceneManager/Scene/BaseScene.h"

class TutorialStage :
	public BaseScene{
public: // メンバ関数

	// コンストラクタ
	TutorialStage();
	// デストラクタ
	~TutorialStage();

	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private: // 関数

	void CheckPlayerProgress();

	// ゲームオーバー時の処理
	void GameOverUpdate();
	// ゲームオーバー時の処理
	void GameOverDraw();

private: // メンバ変数

	ObjectManager objectManager;
	WireManager wireManager;

	Player* player;

	MiddleBoss middleBoss;


	// プレイヤーの進行度フラグ
	int playerProgress;

	// ゲームオーバーかどうか
	bool isGameOver;
	// ゲームオーバー時の背景
	int gameOverColor;
	// 中心から大きくなるための変数
	// 0 ～ 1
	float gameOverT;

};