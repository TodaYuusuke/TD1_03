#pragma once
#include "MyBase/MyBase.h"
#include "Class/SceneManager/Scene/BaseScene.h"

#include "Class/Object/ObjectManager.h"
#include "Class/Wire/WireManager.h"
#include "Class/Map/MapManager.h"

#include "Class/Boss/Boss.h"

#include "Class/AttackHitBox/EnemyAttackHitBox.h"
#include "Class/AttackHitBox/ObjectHitBox.h"

#include "Class/PublicFlag/PublicFlag.h"


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

	ObjectManager objectManager;
	WireManager wireManager;
	Boss boss;
};