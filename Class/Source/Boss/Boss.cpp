#include "Class/Include/Boss/Boss.h"

/*********************************************
 * �{�X�N���X
 *
 * �{�X�֘A�̍s�����ׂĂ��Ǘ�����N���X
 *********************************************/

// �R���X�g���N�^
Boss::Boss() {
	Boss::Initialize();
}

// �f�X�g���N�^
Boss::~Boss() {

}

// ����������
void Boss::Initialize() {
	// �{�X�̈ʒu����ʒ����Ɏ����Ă���
	this->centerPosition = { (float)(BaseConst::kWindowWidth / 2),(float)(BaseConst::kWindowHeight / 2) };
	// �{�X�̉摜�T�C�Y��ݒ�
	this->textureSize = { 225.0f, 450.0f };

	// �s���I����Ԃɂ���
	this->endAction = true;

	// �j�̈ʒu��ݒ�
	coreCenterPosition = centerPosition;
	// �j�̉摜�T�C�Y��ݒ�
	kernelTextureSize = { 256.0f, 256.0f };
}

// �X�V����
void Boss::Update(Point playerPosition) {
	/******** �f�o�b�N���� **********/
	// �f�o�b�O��Ԃ̐؂�ւ�
	if (BaseInput::GetKeyboardState(DIK_0, Trigger)) {
		if (inDebug == false)
			inDebug = true;

		else
			inDebug = false;
	}

	if (endAction == true) {
		if(BaseInput::GetKeyboardState(DIK_F, Trigger)) {
			inAction = true;
		}
	}

	if (inAction == true) {
		Rotate(1440, 2);
	}

	// �f�o�b�O�֐��̎��s
	if (inDebug == true) {
		Debug();
	}

	// �j���������Ă��Ȃ���Ԃł͊j���{�X�ɒǏ]������
	if (coreSeparated == false) {
		coreCenterPosition = centerPosition;
		coreDegree = degree;
	}

	Novice::ScreenPrintf(0, 30, "t : %4.2f", t);
	Novice::ScreenPrintf(0, 50, "pos x : %4.2f y : %4.2f", centerPosition.x, centerPosition.y);
	

}

// �`�揈��
void Boss::Draw() {

	Point viewPosition = { centerPosition.x + shakeVariation.x,centerPosition.y + shakeVariation.y };

	// �{�X�j�摜
	BaseDraw::DrawQuad(
		viewPosition,
		BaseTexture::kBossCore,
		kernelTextureSize,
		1.0f,
		coreDegree,
		0xFFFFFFFF
	);

	// �{�X�����摜
	BaseDraw::DrawQuad(
		Boss::GetLCoverPosition(viewPosition),
		BaseTexture::kBossLCover,
		textureSize,
		1.0f,
		degree,
		0xFFFFFFFF
	);

	// �{�X�E���摜
	BaseDraw::DrawQuad(
		Boss::GetRCoverPosition(viewPosition),
		BaseTexture::kBossRCover,
		textureSize,
		1.0f,
		degree,
		0xFFFFFFFF
	);
}

// �{�X���摜�̑��΍��W�����߂�
Point Boss::GetLCoverPosition(Point centerPosition) { 
	// ��]���S����̍��كx�N�g���쐬
	Point p = { -textureSize.x / 2 - offset, 0 };
	// �x�N�g���v�Z
	p = BaseMath::TurnPoint(p, degree);
	// �v�Z�����l��Ԃ�
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}
// �{�X�E�摜�̑��΍��W�����߂�
Point Boss::GetRCoverPosition(Point centerPosition) { 
	// ��]���S����̍��كx�N�g���쐬
	Point p = { textureSize.x / 2 + offset, 0 };
	// �x�N�g���v�Z
	p = BaseMath::TurnPoint(p, degree);
	// �v�Z�����l��Ԃ�
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}

// �f�o�b�O�p�֐�
void Boss::Debug() {
	// ���ׂĂ����Z�b�g����
	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger)) {
		offset = 0.0f;
		degree = 0;
	}

	// �{�X�����E�ɊJ������
	if (BaseInput::GetKeyboardState(DIK_I, Press))
		offset += 1.0f;

	else if (BaseInput::GetKeyboardState(DIK_K, Press))
		offset -= 1.0f;

	// �I�t�Z�b�g���w��̒l�ȉ��ɂȂ��0�ɂ���
	if (offset < 0) {
		offset = 0;
	}

	// �{�X����]������
	if (BaseInput::GetKeyboardState(DIK_L, Press))
		degree++;

	else if (BaseInput::GetKeyboardState(DIK_J, Press))
		degree--;
}

// �V�F�C�N�֐�
// �Ԃ�l�F�Ȃ�
// �����F
// shakeStrength ... �V�F�C�N����ۂ̋���
// �{�X���V�F�C�N������֐�
void Boss::Shake(int shakeStrength) {
	shakeVariation.x = BaseMath::RandomF(-shakeStrength, shakeStrength, 1);
	shakeVariation.y = BaseMath::RandomF(-shakeStrength, shakeStrength, 1);
}

// �V�F�C�N�C�[�Y�A�E�g�֐�
// �Ԃ�l�F�Ȃ�
// �����F
// shakeStrength ... �V�F�C�N����ۂ̋���
// �{�X���V�F�C�N�����Ȃ���At�̒l�ɂ���Ċ֐�
void ShakeEaseOut(int shakeStrength) {

}

// �s���Ȃ��֐�
// �Ԃ�l�F�Ȃ�
// �����F
// waitTime ... �ҋ@���鎞��
// �s���̍��Ԃɋ��ފ֐��BwaitFrame�͕b���ł͂Ȃ��t���[���P��
void Boss::None(int waitFrame) {
	if (t < waitFrame) {
		t += 1.0f;
	}
	else {
		endAction = true;
	}
}

// ��]�֐�
// �Ԃ�l�F�Ȃ�
// �����F
// endDegree ... �I�����̊p�x
// rotateTime ... ��]���鎞�ԁB����͕b��
// �{�X����]������֐�
void Boss::Rotate(float endDegree, int RotateTime) {

	static int startDegree;
	// ����������
	if (init == false) {
		startDegree = degree;
		init = true;
	}

	// t �̒l�����ȏ�ɂȂ�܂ő���
	if (t <= RotateTime) {
		t += 1.0f / 60.0f;
		inAction = true;
		// �C�[�W���O��p���ĉ�]
		degree = BaseDraw::Ease_InOut(t, startDegree, endDegree, RotateTime);
	}
	else {
		//t �����ȏ�ɂȂ�����s���I��
		t = 0.0f;
		degree = 0;
		init = false;
		endAction = true;
		inAction = false;
	}
}

// �ːi�֐�
// �Ԃ�l�F�Ȃ�
// �����F
// startPosition ... �J�n���ʒu
// playerPosition ... �v���C���[�̈ʒu(Point)
// playerDirection ... �v���C���[�ւ̃x�N�g��
// �{�X���v���C���[�̌����ɓːi������֐�
void Boss::Rush(Point startPosition, Point playerPosition, float playerDirection) {
	// ����������
	if (init = false) {
		playerDirection = atan2(playerPosition.y - centerPosition.y, playerPosition.x - centerPosition.x);
		init = true;
	}

	// t �̒l�����ȏ�ɂȂ�܂ő���
	if (t < 1.0f) {
		switch (actionWayPoint)
		{
		case Boss::WAYPOINT1:

			break;
		case Boss::WAYPOINT2:

			break;
		case Boss::WAYPOINT3:

			break;
		case Boss::WAYPOINT4:
			break;
		case Boss::WAYPOINT5:
			break;
		default:
			break;
		}
		t += 0.01f;
		
	}
	else {
		switch (actionWayPoint)
		{
		case Boss::WAYPOINT1:

			break;
		case Boss::WAYPOINT2:

			break;
		case Boss::WAYPOINT3:

			break;
		case Boss::WAYPOINT4:
			break;
		case Boss::WAYPOINT5:
			break;
		default:
			break;
		}

		//t �����ȏ�ɂȂ�����s���I��
		t = 0.0f;
		init = false;
		endAction = true;
		inAction = false;
	}
}


#pragma region �R�s�y�p
//// ����������
//if (init = false) {
//	init = true;
//}
//
//// t �̒l�����ȏ�ɂȂ�܂ő���
//if (t < 1.0f) {
//	t += 0.01f;
//
//}
//else {
//	//t �����ȏ�ɂȂ�����s���I��
//	t = 0.0f;
//	init = false;
//	endAction = true;
//	inAction = false;
//}
#pragma endregion
