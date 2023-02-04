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

	ObjectHitBox::Initialize();
	MapManager::TutorialInitialize();
	objectManager.Initialize();
	wireManager.Initialize();

	objectManager.MakeNewObjectPlayer({ 100,700 }, &wireManager);
}
// �X�V
void TutorialStage::Update() {
	// �����蔻��̏�����
	EnemyAttackHitBox::Initialize();

	// �f�o�b�O�p
	if (BaseInput::GetKeyboardState(DIK_RETURN, Trigger)) {
		nextScene = sceneBossStage;
	} 
	// �萔�̃z�b�g�����[�h
	if (BaseInput::GetKeyboardState(DIK_F1, Trigger)) {
		PublicFlag::Initialize();

		ObjectHitBox::Initialize();
		MapManager::TutorialInitialize();
	}

	//MapManager::Update();
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