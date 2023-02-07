#pragma once
#include "MyBase/MyBase.h"
#include "Class/SceneManager/Scene/BaseScene.h"

class Title :
	public BaseScene{
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
};