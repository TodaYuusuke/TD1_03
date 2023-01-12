#include "MyBase/Include/Other/BaseDraw.h"

using namespace BaseStruct;

// �X�N���[�����W�n


// �Q�b�g�X�N���[�����W�֐�
// �Ԃ�l�F�X�N���[���̍��W�iPoint�j
// �����F����
// �X�N���[���̍��W�����̂܂܎󂯎��֐�
Point BaseDraw::GetScreenPosition() {
	return screenPosition;
}

// �Z�b�g�X�N���[�����W�֐�
// �Ԃ�l�F����
// �����F
// setPosition ... �Z�b�g������W
// �X�N���[���̍��W���Z�b�g����֐�
void BaseDraw::SetScreenPosition(Point setPosition) {
	screenPosition = setPosition;
}

// ���[���h���W���X�N���[�����W�ɂ��ĕԂ��֐�
// �Ԃ�l�F�ϊ����ꂽ�X�N���[�����W
// �����F
// worldPosition ... ���[���h���W
// ���[���h���W���X�N���[�����W�ɕϊ��������Ƃ��Ɏg���֐�
Point BaseDraw::WorldtoScreen(Point worldPosition) {
	return { worldPosition.x - screenPosition.x, (worldPosition.y - screenPosition.y) * -1 };
}

// �X�N���[�����W�����[���h���W�ɂ��ĕԂ��֐�
// �Ԃ�l�F�ϊ����ꂽ���[���h���W
// �����F
// screenPosition ... �X�N���[�����W
// �X�N���[�����W�����[���h���W�ɕϊ��������Ƃ��Ɏg���֐�
Point BaseDraw::ScreentoWorld(Point _screenPosition) {
	return { _screenPosition.x + screenPosition.x, _screenPosition.y * -1 + screenPosition.y };
}

// �t���X�N���[�����[�h��؂�ւ���֐�
// �Ԃ�l�F�Ȃ�
// �����F�Ȃ�
void BaseDraw::ChangeFullScreen() {
	if (isFullScreen) {
		Novice::SetWindowMode(kWindowed);
		isFullScreen = false;
	}
	else {
		Novice::SetWindowMode(kFullscreen);
		isFullScreen = true;
	}
}


// �e��`��֐��̃��[���h���W�Ή�Ver


// ���[���h���W����X�v���C�g��`�悷��֐��iDrawSprite�j
// �Ԃ�l�F����
// �����F
// worldPosition ... �`�悷��X�v���C�g�̍�����W
// textureHandle ... �e�N�X�`���̃n���h��
// scale ... �`�悷��X�v���C�g�̔{��
// angle ... �`�悷��X�v���C�g�̉�]�p�iDegree�j
// color ... �`�悷��X�v���C�g�̐F
// ���[���h���W�̂܂܌Ăяo����`��֐��iDrawSprite�j
void BaseDraw::DrawSprite(Point worldPosition, int textureHandle, Point scale, float angle, unsigned int color) {
	Point screenPos = WorldtoScreen(worldPosition);
	Novice::DrawSprite(screenPos.x, screenPos.y, textureHandle, scale.x, scale.y, angle, color);
}

// ���[���h���W����X�v���C�g��`�悷��֐��iDrawQuad�j
// �Ԃ�l�F����
// �����F
// worldPosition ... �`�悷��X�v���C�g�̒��S���W
// textureHandle ... �e�N�X�`���̃n���h��
// textureSize ... �e�N�X�`���̃T�C�Y
// scale ... �`�悷��X�v���C�g�̔{��
// angle ... �`�悷��X�v���C�g�̉�]�p�iDegree�j
// color ... �`�悷��X�v���C�g�̐F
// ���[���h���W�̂܂܌Ăяo����`��֐��iDrawQuad�j
void BaseDraw::DrawQuad(Point worldPosition, int textureHandle, Point textureSize, float scale, float angle, unsigned int color) {

	// �l�p�����߂�
	Quad quad = {
		-textureSize.x / 2.0f * scale,
		-textureSize.y / 2.0f * scale,
		+textureSize.x / 2.0f * scale,
		-textureSize.y / 2.0f * scale,
		-textureSize.x / 2.0f * scale,
		+textureSize.y / 2.0f * scale,
		+textureSize.x / 2.0f * scale,
		+textureSize.y / 2.0f * scale
	};

	// ��]
	quad = BaseMath::TurnBox(quad, angle);
	// �X�N���[�����W��
	quad.q1 = WorldtoScreen({ quad.q1.x + worldPosition.x, quad.q1.y + worldPosition.y });
	quad.q2 = WorldtoScreen({ quad.q2.x + worldPosition.x, quad.q2.y + worldPosition.y });
	quad.q3 = WorldtoScreen({ quad.q3.x + worldPosition.x, quad.q3.y + worldPosition.y });
	quad.q4 = WorldtoScreen({ quad.q4.x + worldPosition.x, quad.q4.y + worldPosition.y });

	// �`��
	Novice::DrawQuad(
		quad.q1.x, quad.q1.y,
		quad.q2.x, quad.q2.y,
		quad.q3.x, quad.q3.y,
		quad.q4.x, quad.q4.y,
		0, 0,
		textureSize.x, textureSize.y,
		textureHandle,
		color
	);
}


//////////////////////////////////
/* - static�����o�ϐ��̎��Ԃ�錾 - */
//////////////////////////////////

// ���݂̃��[�h��
Point BaseDraw::screenPosition;
bool BaseDraw::isFullScreen = false;