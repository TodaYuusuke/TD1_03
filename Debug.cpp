 #include "Debug.h"

// �R���X�g���N�^
Debug::Debug() {

}
// �f�X�g���N�^
Debug::~Debug() {

}


// ������
void Debug::Initialize() {
	ObjectHitBox::Initialize();
	MapManager::Initialize();
	objectManager.Initialize();
	wireManager.Initialize();
	objectManager.MakeNewObjectPlayer({ 100,200 }, &wireManager);
	boss.Initialize(&objectManager);
}
// �X�V
void Debug::Update() {

	Novice::ScreenPrintf(0, 0, "Move ... WASD");
	Novice::ScreenPrintf(0, 20, "SPACE ... JAMP");
	Novice::ScreenPrintf(0, 40, "SHOT WIRE ... LEFTCLICK");
	Novice::ScreenPrintf(0, 60, "ATTARACT ... RIGHTCLICK");
	Novice::ScreenPrintf(0, 80, "RESTART ... R");

	// ���t���[�������蔻���������
	EnemyAttackHitBox::Initialize();

	// B�L�[�Ńu���b�N�𐶐�
	if (BaseInput::GetKeyboardState(DIK_B, Trigger)) {
		//objectManager.MakeNewObjectBlock(BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()), { 50,50 });
	}

	// R�L�[�Ń��Z�b�g
	if (BaseInput::GetKeyboardState(DIK_R, Trigger)) {
		ObjectHitBox::Initialize();
		MapManager::Initialize();
		objectManager.Initialize();
		wireManager.Initialize();
		objectManager.MakeNewObjectPlayer({ 100,200 }, &wireManager);
		boss.Initialize(&objectManager);
	}

	// E�L�[�ŎG���I����
	if (BaseInput::GetKeyboardState(DIK_E, Trigger)) {
		//objectManager.MakeNewObjectEnemy(BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()), { 50,50 });
	}

	MapManager::Update();
	boss.Update(objectManager.GetPlayerPosition(), &objectManager, &wireManager);
	objectManager.Update();
	wireManager.Update(&objectManager);
}
// �`��
void Debug::Draw() {

	MapManager::Draw();
	boss.Draw();
	objectManager.Draw();
	wireManager.Draw();

	Novice::DrawEllipse(BaseInput::GetMousePosition().x, BaseInput::GetMousePosition().y, 2, 2, 0, GREEN, kFillModeWireFrame);
	Novice::DrawEllipse(BaseInput::GetMousePosition().x, BaseInput::GetMousePosition().y, 10, 10, 0, GREEN, kFillModeWireFrame);
	Novice::DrawEllipse(BaseInput::GetMousePosition().x, BaseInput::GetMousePosition().y, 11, 11, 0, GREEN, kFillModeWireFrame);
	Novice::DrawEllipse(BaseInput::GetMousePosition().x, BaseInput::GetMousePosition().y, 12, 12, 0, GREEN, kFillModeWireFrame);
}