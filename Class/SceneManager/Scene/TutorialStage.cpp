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
}
// 更新
void TutorialStage::Update() {

	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger)) {
		nextScene = sceneBossStage;
	}

}
// 描画
void TutorialStage::Draw() {
	Novice::ScreenPrintf(1920 / 2, 1080 / 2, "TutorialStage");
	Novice::ScreenPrintf(1920 / 2, 1080 / 2 + 20, "Push Space to next");
}