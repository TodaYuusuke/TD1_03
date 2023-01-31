#include "Class/SceneManager/Scene/BossStage.h"

// �R���X�g���N�^
BossStage::BossStage() {
	Initialize();
}
// �f�X�g���N�^
BossStage::~BossStage() {

}



// ������
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
// �X�V
void BossStage::Update() {

	if(BaseInput::GetKeyboardState(DIK_E, Trigger)) {
		PublicFlag::kisStaging = !PublicFlag::kisStaging;
	}

	MapManager::Update();
	boss.Update(objectManager.GetPlayerPosition(), &objectManager, &wireManager);
	objectManager.Update();
	wireManager.Update(&objectManager);

}
// �`��
void BossStage::Draw() {

	MapManager::Draw();
	boss.Draw();
	objectManager.Draw();
	wireManager.Draw();
}