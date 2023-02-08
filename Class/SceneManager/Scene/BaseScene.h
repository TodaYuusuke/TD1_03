#pragma once
#include "MyBase/MyBase.h"

#include "Class/Object/ObjectManager.h"
#include "Class/Wire/WireManager.h"
#include "Class/Map/MapManager.h"

#include "Class/MiddleBoss/MiddleBoss.h"
#include "Class/Boss/Boss.h"

#include "Class/AttackHitBox/EnemyAttackHitBox.h"
#include "Class/AttackHitBox/ObjectHitBox.h"

#include "Class/PublicFlag/PublicFlag.h"

class BaseScene {
public: // メンバ関数

	// 初期化
	virtual void Initialize() {
		nextScene = sceneNone;
	}
	// 更新
	virtual void Update() {

	}
	// 描画
	virtual void Draw() {

	}

	// シーン変更を告げる関数
	// 返り値：シーン変更しない場合 ... None
	// 　　　　　　　　　　する場合 ... 変更先のシーン
	virtual SceneState isGoNextScene() {
		return nextScene;
	}


protected: // メンバ変数

	// 次のシーン
	SceneState nextScene;
};