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
	void Initialize(int);
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


	// 前回のスクリーン座標
	float preScrollPositionX;
	// 背景スクロール用
	float backGroundPositionX[3];


	// リスポーン地点のフラグ
	int respawnProgress;
	// 演出用のフラグ
	int gimmickProgress;
	// ネオン用経過フレーム
	int neonFrame;
	
	// コントローラを含めた座標
	Point reticlePosition;
	Point preMousePosition;

	// ゲームオーバーかどうか
	bool isGameOver;
	// ゲームオーバー時の背景
	int gameOverColor;
	// 中心から大きくなるための変数
	// 0 ～ 1
	float gameOverT;
	// タイトルへ～を選択しているか
	bool isToTitle;
	// リトライを選択しているか
	bool isToRetry;


};