#pragma once
#include "Base/Include/Define/BaseStruct.h"
#include "Base/Include/Other/BaseMath.h"

#include <Novice.h>

class BaseDraw {

public:


	// �X�N���[�����W�֘A


	// �Q�b�g�X�N���[�����W�֐�
	// �Ԃ�l�F�X�N���[���̍��W�iPoint�j
	// �����F����
	// �X�N���[���̍��W�����̂܂܎󂯎��֐�
	static Point GetScreenPosition();

	// �Z�b�g�X�N���[�����W�֐�
	// �Ԃ�l�F����
	// �����F
	// setPosition ... �Z�b�g������W
	// �X�N���[���̍��W���Z�b�g����֐�
	static void SetScreenPosition(Point setPosition);

	// ���[���h���W���X�N���[�����W�ɂ��ĕԂ��֐�
	// �Ԃ�l�F�ϊ����ꂽ�X�N���[�����W
	// �����F
	// worldPosition ... ���[���h���W
	// ���[���h���W���X�N���[�����W�ɕϊ��������Ƃ��Ɏg���֐�
	static Point WorldtoScreen(Point worldPosition);

	// �X�N���[�����W�����[���h���W�ɂ��ĕԂ��֐�
	// �Ԃ�l�F�ϊ����ꂽ���[���h���W
	// �����F
	// screenPosition ... �X�N���[�����W
	// �X�N���[�����W�����[���h���W�ɕϊ��������Ƃ��Ɏg���֐�
	static Point ScreentoWorld(Point _screenPosition);

	// �t���X�N���[�����[�h��؂�ւ���֐�
	// �Ԃ�l�F�Ȃ�
	// �����F�Ȃ�
	static void ChangeFullScreen();



	// �C�[�W���O�֐�
	// �Ԃ�l�F����
	// �����F
	// t ... ���݂̃^�C���l(�b)
	// b ... �v���p�e�B�̏��߂̒l
	// c ... �v���p�e�B�̏��߂̒l�ƏI���̒l�Ƃ̍�(�ω���)
	// d ... �A�j���[�V�����̎��ԁi�b�j
	static float Linear(float t, float  b, float  c, float  d) {
		return c * t / d + b;
	};
	// �C�[�W���O�֐�
	// �Ԃ�l�F����
	// �����F
	// t ... ���݂̃^�C���l(�b)
	// b ... �v���p�e�B�̏��߂̒l
	// c ... �v���p�e�B�̏��߂̒l�ƏI���̒l�Ƃ̍�(�ω���)
	// d ... �A�j���[�V�����̎��ԁi�b�j
	static float Ease_In(float t, float b, float c, float d) {
		t /= d;
		return c * t * t + b;
	}
	// �C�[�W���O�֐�
	// �Ԃ�l�F����
	// �����F
	// t ... ���݂̃^�C���l(�b)
	// b ... �v���p�e�B�̏��߂̒l
	// c ... �v���p�e�B�̏��߂̒l�ƏI���̒l�Ƃ̍�(�ω���)
	// d ... �A�j���[�V�����̎��ԁi�b�j
	static float Ease_Out(float t, float b, float c, float d) {
		t /= d;
		return -c * t * (t - 2.0) + b;
	}
	// �C�[�W���O�֐�
	// �Ԃ�l�F����
	// �����F
	// t ... ���݂̃^�C���l(�b)
	// b ... �v���p�e�B�̏��߂̒l
	// c ... �v���p�e�B�̏��߂̒l�ƏI���̒l�Ƃ̍�(�ω���)
	// d ... �A�j���[�V�����̎��ԁi�b�j
	static float Ease_InOut(float t, float b, float c, float d) {
		return -c / 2.0 * (cosf(M_PI * t / d) - 1) + b;
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
	static void DrawSprite(Point worldPosition, int textureHandle, Point scale, float angle, unsigned int color);

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
	static void DrawQuad(Point worldPosition, int textureHandle, Point textureSize, float scale, float angle, unsigned int color);


private:

	// �X�N���[�����W
	static Point screenPosition;
	// ���݃t���X�N���[�����ǂ���
	static bool isFullScreen;
};