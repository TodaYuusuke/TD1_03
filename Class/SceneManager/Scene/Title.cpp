#include "Class/SceneManager/Scene/Title.h"

// �R���X�g���N�^
Title::Title() {
	Initialize();
}
// �f�X�g���N�^
Title::~Title() {

}



// ������
void Title::Initialize() {
	nextScene = sceneNone;
}
// �X�V
void Title::Update() {

	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger)) {
		nextScene = sceneTutorialStage;
	}

}
// �`��
void Title::Draw() {
	Novice::ScreenPrintf(1920 / 2, 1080 / 2, "Title");
	Novice::ScreenPrintf(1920 / 2, 1080 / 2 + 20, "Push Space to next");
}