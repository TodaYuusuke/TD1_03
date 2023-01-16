 #include "Debug.h"

// �R���X�g���N�^
Debug::Debug() {

}
// �f�X�g���N�^
Debug::~Debug() {

}


// ������
void Debug::Initialize() {
	MapManager::Initialize();
	objectManager.Initialize();
	wireManager.Initialize();
}
// �X�V
void Debug::Update() {

	// ���N���b�N�Ńu���b�N�𐶐�
	if (BaseInput::GetMouseState(MiddleClick, Trigger)) {
		objectManager.MakeNewObjectBlock(BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()), { 50,50 });
	}
	// ���N���b�N�Ń��C���[���ˏo�i�ˏo�n�_��100,100�ŌŒ�j
	if (BaseInput::GetMouseState(LeftClick, Trigger)) {
		//wireManager.Shot({ 100,100 }, BaseMath::GetDegree({ 100,100 }, BaseDraw::ScreentoWorld(BaseInput::GetMousePosition())),);
	}

	if (BaseInput::GetKeyboardState(DIK_Q, Trigger)) {
		objectManager.MakeNewObjectPlayer({ 200,200 });
	}

	// R�L�[�Ń��Z�b�g
	if (BaseInput::GetKeyboardState(DIK_R, Trigger)) {
		MapManager::Initialize();
		objectManager.Initialize();
		wireManager.Initialize();
	}



	// �X�N���[�����W�̈ړ���
	Point screenPosMove = BaseDraw::GetScreenPosition();
	if (BaseInput::GetKeyboardState(DIK_UP, Press)) {
		screenPosMove.y += 5;
	}
	if (BaseInput::GetKeyboardState(DIK_DOWN, Press)) {
		screenPosMove.y -= 5;
	}
	if (BaseInput::GetKeyboardState(DIK_RIGHT, Press)) {
		screenPosMove.x += 5;
	}
	if (BaseInput::GetKeyboardState(DIK_LEFT, Press)) {
		screenPosMove.x -= 5;
	}
	BaseDraw::SetScreenPosition(screenPosMove);



	MapManager::Update();
	objectManager.Update();
	wireManager.Update(&objectManager);
}
// �`��
void Debug::Draw() {

	MapManager::Draw();
	objectManager.Draw();
	wireManager.Draw();
}