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

	// シーン変更を告げる関数
	// 返り値：シーン変更しない場合 ... None
	// 　　　　　　　　　　する場合 ... 変更先のシーン
	SceneState isGoNextScene() override {
		if (nextScene != sceneNone) {
			if (BaseEffectManager::isEndEffect(fadeEnd)) {
				return nextScene;
			}
		}
		return sceneNone;
	}

private: // メンバ関数

	// ゲームオーバー時の処理
	void GameOverUpdate();
	// ゲームオーバー時の処理
	void GameOverDraw();


private: // メンバ変数

	ObjectManager objectManager;
	WireManager wireManager;
	Boss boss;

	// 前回のスクリーン座標
	float preScrollPositionX;
	// 背景スクロール用
	float backGroundPositionX[3];

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

	// フェードインアウト確認用フラグ
	int fadeEnd;
};