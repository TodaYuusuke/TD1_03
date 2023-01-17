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

	// �f�o�b�O�֐��̎��s
	if (inDebug == true) {
		Debug();
	}

	// �j���������Ă��Ȃ���Ԃł͊j���{�X�ɒǏ]������
	if (coreSeparated == false) {
		coreCenterPosition = centerPosition;
		coreDegree = degree;
	}

}

// �`�揈��
void Boss::Draw() {
	// �{�X�j�摜
	BaseDraw::DrawQuad(
		coreCenterPosition,
		BaseTexture::kBossCore,
		kernelTextureSize,
		1.0f,
		coreDegree,
		0xFFFFFFFF
	);

	// �{�X�����摜
	BaseDraw::DrawQuad(
		Boss::GetLCoverPosition(centerPosition),
		BaseTexture::kBossLCover,
		textureSize,
		1.0f,
		degree,
		0xFFFFFFFF
	);

	// �{�X�E���摜
	BaseDraw::DrawQuad(
		Boss::GetRCoverPosition(centerPosition),
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

// �s���Ȃ��i�s���Ԃ̑ҋ@���ԂƂ��ėp����j
void Boss::None(int waitTime) {
	if (t < waitTime) {
		t += 1.0f;
	}
	else {
		endAction = true;
	}
}