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

private: // メンバ変数

	ObjectManager objectManager;
	WireManager wireManager;

	Player* player;

	MiddleBoss middleBoss;
};