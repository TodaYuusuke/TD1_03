#pragma once
#include "MyBase/MyBase.h"
#include "Class/SceneManager/Scene/BaseScene.h"

class Start :
	public BaseScene {
public: // メンバ関数

	// コンストラクタ
	Start();
	// デストラクタ
	~Start();

	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

	SceneState isGoNextScene() override {
		return sceneTitle;
	}

private: // メンバ変数
};