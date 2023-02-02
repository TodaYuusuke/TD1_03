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

	PublicFlag::Initialize();
	
	MapManager::BossInitialize();
	objectManager.Initialize();
	wireManager.Initialize();

	objectManager.MakeNewObjectPlayer({ 100,700 }, &wireManager);
}
// �X�V
void TutorialStage::Update() {
	// �f�o�b�O�p
	if (BaseInput::GetKeyboardState(DIK_RETURN, Trigger)) {
		nextScene = sceneBossStage;
	}

	MapManager::Update();
	objectManager.Update();
	wireManager.Update(&objectManager);
}
// �`��
void TutorialStage::Draw() {
	// �f�o�b�O�p
	Novice::ScreenPrintf(0, 0, "Push ENTER to Skip Stage");

	MapManager::Draw();
	objectManager.Draw();
	wireManager.Draw();
}