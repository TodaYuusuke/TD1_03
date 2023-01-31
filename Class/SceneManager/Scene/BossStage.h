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

private: // メンバ変数
};