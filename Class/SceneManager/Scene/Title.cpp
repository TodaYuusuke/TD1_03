#include "Class/SceneManager/Scene/Title.h"

// コンストラクタ
Title::Title() {
	Initialize();
}
// デストラクタ
Title::~Title() {

}



// 初期化
void Title::Initialize() {
	nextScene = sceneNone;
}
// 更新
void Title::Update() {

	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger)) {
		nextScene = sceneTutorialStage;
	}

}
// 描画
void Title::Draw() {
	Novice::ScreenPrintf(1920 / 2, 1080 / 2, "Title");
	Novice::ScreenPrintf(1920 / 2, 1080 / 2 + 20, "Push Space to next");
}