#include "Class/SceneManager/Scene/BossStage.h"

// コンストラクタ
BossStage::BossStage() {
	Initialize();
}
// デストラクタ
BossStage::~BossStage() {

}



// 初期化
void BossStage::Initialize() {
	nextScene = sceneNone;

	PublicFlag::Initialize();
	ObjectHitBox::Initialize();
	MapManager::Initialize();
	objectManager.Initialize();
	wireManager.Initialize();
	objectManager.MakeNewObjectPlayer({ 100,200 }, &wireManager);
	boss.Initialize(&objectManager);
}
// 更新
void BossStage::Update() {

	if(BaseInput::GetKeyboardState(DIK_E, Trigger)) {
		PublicFlag::kisStaging = !PublicFlag::kisStaging;
	}

	MapManager::Update();
	boss.Update(objectManager.GetPlayerPosition(), &objectManager, &wireManager);
	objectManager.Update();
	wireManager.Update(&objectManager);

}
// 描画
void BossStage::Draw() {

	MapManager::Draw();
	boss.Draw();
	objectManager.Draw();
	wireManager.Draw();
}