#pragma once
#include "MyBase/MyBase.h"
#include "Class/SceneManager/Scene/BaseScene.h"

class GameClear :
	public BaseScene {
public: // メンバ関数

	// コンストラクタ
	GameClear();
	// デストラクタ
	~GameClear();

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
			Novice::StopAudio(bgmHandle);
		}
		return nextScene;
	}

private: // メンバ変数

	// コントローラを含めた座標
	Point reticlePosition;
	Point preMousePosition;
	// スタートを選択しているか
	bool isToTitle;
	bool isToEnd;
	// 選択したか
	bool isSelected;

	// フェードアウト用
	int feedOutFlame;
	int feedInFlame;

	const int kFeedInMax = 60;
	const int kFeedOutMax = 60;


	// bgmハンドル
	static int bgmHandle;
};