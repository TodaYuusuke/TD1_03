#include "Debug.h"

// �R���X�g���N�^
Debug::Debug() {

}
// �f�X�g���N�^
Debug::~Debug() {

}


// ������
void Debug::Initialize() {
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
	// �E�N���b�N�Ńu���b�N�𐶐�
	if (BaseInput::GetMouseState(MiddleClick, Trigger)) {
		wireManager.Attract();
	}

	if (BaseInput::GetKeyboardState(DIK_Q, Trigger)) {
		objectManager.MakeNewObjectPlayer({ 200,200 });
	}

	objectManager.Update();
	wireManager.Update(objectManager);
}
// �`��
void Debug::Draw() {
	objectManager.Draw();
	wireManager.Draw();
}