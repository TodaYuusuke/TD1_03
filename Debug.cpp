 #include "Debug.h"

// �R���X�g���N�^
Debug::Debug() {

}
// �f�X�g���N�^
Debug::~Debug() {

}


// ������
void Debug::Initialize() {

	hitBox = { {100,300},50,50 };

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

	Novice::ScreenPrintf(0, 0, "%f %f", BaseDraw::WorldtoScreen(BaseInput::GetMousePosition()).x, BaseDraw::WorldtoScreen(BaseInput::GetMousePosition()).y);
	Novice::ScreenPrintf(0, 20, "%f %f", BaseDraw::GetScreenPosition().x, BaseDraw::GetScreenPosition().y);

	MapManager::Draw();
	objectManager.Draw();
	wireManager.Draw();
}