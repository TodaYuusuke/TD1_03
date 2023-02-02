#include "Class/SceneManager/Scene/TutorialStage.h"

// コンストラクタ
TutorialStage::TutorialStage() {
	Initialize();
}
// デストラクタ
TutorialStage::~TutorialStage() {

}



// 初期化
void TutorialStage::Initialize() {
	nextScene = sceneNone;

	PublicFlag::Initialize();
	
	MapManager::BossInitialize();
	objectManager.Initialize();
	wireManager.Initialize();

	objectManager.MakeNewObjectPlayer({ 100,700 }, &wireManager);
}
// 更新
void TutorialStage::Update() {
	// デバッグ用
	if (BaseInput::GetKeyboardState(DIK_RETURN, Trigger)) {
		nextScene = sceneBossStage;
	}

	MapManager::Update();
	objectManager.Update();
	wireManager.Update(&objectManager);
}
// 描画
void TutorialStage::Draw() {
	// デバッグ用
	Novice::ScreenPrintf(0, 0, "Push ENTER to Skip Stage");

	MapManager::Draw();
	objectManager.Draw();
	wireManager.Draw();
}