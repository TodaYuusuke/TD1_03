#include "MyBase/Include/Other/BaseInput.h"


// ������
void BaseInput::Initialize() {

	// �����o�ϐ��̏�����

	// �}�E�X���W
	mousePosition = { 0,0 };

	// �L�[���͂̏�����
	for (int i = 0; i < 256; i++) {
		keys[i] = { 0 };
		preKeys[i] = { 0 };
	}
}
// �X�V
void BaseInput::Update() {

	// �}�E�X���W���X�V
	int x = 0, y = 0;
	Novice::GetMousePosition(&x, &y);
	mousePosition = { (float)x,(float)y };

	// �L�[���͂��󂯎��
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

}
// �`��
void BaseInput::Draw() {

}



// �}�E�X���W���󂯎��֐�
// �Ԃ�l�F�}�E�X���W��Point
// �����F����
// �}�E�X�̍��W��Point�^�Ŏ󂯎��֐�
Point BaseInput::GetMousePosition() {
	return mousePosition;
}


// �}�E�X�̓��͏�Ԃ��󂯎��֐�
// �Ԃ�l�Fkey �� state �̏ꍇ -> true �����łȂ��ꍇ -> false
// �����F
// key ... ���؂���L�[
// state ... ���؂��������
// ����̃L�[���ǂ�ȏ�ԁiNull,Trigger,Press,Release�j�����`�F�b�N����֐��iRelease�������j
bool BaseInput::GetMouseState(MouseButton key, InputState state) {
	switch (state)
	{
		// ������Ă��Ȃ�
		case Null:
			// ������Ă��Ȃ� ������
			if (!Novice::IsTriggerMouse(key) && !Novice::IsPressMouse(key)) {
				return true;
			}
			else {
				return false;
			}

		// �����ꂽ�u��
		case Trigger:
			// �����ꂽ�u�� ������
			if (Novice::IsTriggerMouse(key)) {
				return true;
			}
			else {
				return false;
			}

		// �������ςȂ�
		case Press:
			// �������ςȂ� ������
			if (Novice::IsPressMouse(key)) {
				return true;
			}
			else {
				return false;
			}

		// �����ꂽ�u��
		case Release:
			// �����ꂽ�u�� ������
			
			// ������
		
		// �G���[
		default:
			return false;
	}
}


// �L�[�̓��͏�Ԃ��󂯎��֐�
// �Ԃ�l�Fkey �� state �̏ꍇ -> true �����łȂ��ꍇ -> false
// �����F
// key ... ���؂���L�[
// state ... ���؂��������
// ����̃L�[���ǂ�ȏ�ԁiNull,Trigger,Press,Release�j�����`�F�b�N����֐�
bool BaseInput::GetKeyboardState(int key, InputState state) {
	switch (state)
	{
		// ������Ă��Ȃ�
		case Null:
			// ������Ă��Ȃ� ������
			if (!keys[key] && !preKeys[key]) {
				return true;
			}
			else {
				return false;
			}
			// �����ꂽ�u��
		case Trigger:
			// �����ꂽ�u�� ������
			if (keys[key] && !preKeys[key]) {
				return true;
			}
			else {
				return false;
			}
			// �������ςȂ�
		case Press:
			// �������ςȂ� ������
			if (keys[key]) {
				return true;
			}
			else {
				return false;
			}
			// �����ꂽ�u��
		case Release:
			// �����ꂽ�u�� ������
			if (!keys[key] && preKeys[key]) {
				return true;
			}
			else {
				return false;
			}
			// �G���[
		default:
			return false;
	}
}


// �}�E�X���t�H�[���ɌŒ肷��֐�
// �Ԃ�l�F����
// �����F����
// �}�E�X���t�H�[�����ɌŒ肷��֐�
void BaseInput::ClipMouseinFoam() {
	// �}�E�X�̃N���C�A���g���W
	LPPOINT mouseClientPos = new tagPOINT();
	GetCursorPos(mouseClientPos);

	// �t�H�[���̍��W�����߂�
	LONG foamPositionX = { mouseClientPos->x - (LONG)mousePosition.x };
	LONG foamPositionY = { mouseClientPos->y - (LONG)mousePosition.y };

	// �J�[�\���ړ�����
	const RECT rect = { foamPositionX, foamPositionY + 1, foamPositionX + BaseConst::kWindowWidth, foamPositionY + BaseConst::kWindowHeight };
	ClipCursor(&rect);
}


// �}�E�X�����͈͂ɌŒ肷��֐�
// �Ԃ�l�F����
// �����F
// position ... �Œ肷��N���C�A���g���W�ix,y�j
// length ... �Œ肷��͈́iwidth,height�j
// �}�E�X�����͈̔͂ɌŒ肷��֐�
void BaseInput::ClipMouseinRectangle(Point position, Point length) {
	// �J�[�\���ړ�����
	const RECT rect = { position.x, position.y, position.x + length.x, position.y + length.y };
	ClipCursor(&rect);
}


// �Œ肵���}�E�X���������֐�
// �Ԃ�l�F����
// �����F����
// �}�E�X�̌Œ����������֐��B�Œ肵����͕K���Ăяo�����ƁI�I�I�I�I
void BaseInput::ClipMouseClear() {
	ClipCursor(NULL);
}


//////////////////////////////////
/* - static�����o�ϐ��̎��Ԃ�錾 - */
//////////////////////////////////

// �}�E�X���W
Point BaseInput::mousePosition;

// �L�[�̓��͏󋵁i����̃t���[���j
char BaseInput::keys[256];
// �L�[�̓��͏󋵁i�O��̃t���[���j
char BaseInput::preKeys[256];