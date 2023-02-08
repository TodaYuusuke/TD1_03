#pragma once
#include "MyBase/MyBase.h"
#include "Class/SceneManager/Scene/BaseScene.h"

class Title :
	public BaseScene {
public: // メンバ関数

	// コンストラクタ
	Title();
	// デストラクタ
	~Title();

	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private: // メンバ変数

	// コントローラを含めた座標
	Point reticlePosition;
	Point preMousePosition;
	// スタートを選択しているか
	bool isToPlay;
	bool isToEnd;
	// 選択したか
	bool isSelected;

	// フェードアウト用
	int feedOutFlame;
	int feedInFlame;

	const int kFeedInMax = 60;
	const int kFeedOutMax = 60;

};