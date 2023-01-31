#include "Class/SceneManager/Scene/TutorialStage.h"

// �R���X�g���N�^
TutorialStage::TutorialStage() {
	Initialize();
}
// �f�X�g���N�^
TutorialStage::~TutorialStage() {

}



// ������
void TutorialStage::Initialize() {
	nextScene = sceneNone;
}
// �X�V
void TutorialStage::Update() {

	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger)) {
		nextScene = sceneBossStage;
	}

}
// �`��
void TutorialStage::Draw() {
	Novice::ScreenPrintf(1920 / 2, 1080 / 2, "TutorialStage");
	Novice::ScreenPrintf(1920 / 2, 1080 / 2 + 20, "Push Space to next");
}