#pragma once
#include "MyBase/MyBase.h"

#include "Class/SceneManager/Scene/BaseScene.h"
#include "Class/SceneManager/Scene/Title.h"
#include "Class/SceneManager/Scene/TutorialStage.h"
#include "Class/SceneManager/Scene/BossStage.h"
#include "Class/SceneManager/Scene/GameClear.h"

class SceneManager {
public: // メンバ関数

	// コンストラクタ
	SceneManager();
	// デストラクタ
	~SceneManager();

	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();


private: // メンバ変数

	// 現在のシーン
	BaseScene* currentScene;
};