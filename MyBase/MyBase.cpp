#include "MyBase/MyBase.h"


// ������
void MyBase::Initialize() {

	// �e�N�X�`���̏�����
	BaseTexture::Initialize();
	// �e�N�X�`���̃��[�h�i�{���̎g�����Ƃ͈Ⴄ���A����͂���ł����j
	BaseTexture::Loading();
	// �I�[�f�B�I�̏�����
	BaseAudio::Initialize();
	BaseAudio::InitializeVolume();
	// �I�[�f�B�I�̃��[�h�i�{���̎g�����Ƃ͈Ⴄ���A����͂���ł����j
	BaseAudio::Loading();
	// �萔�̏�����
	BaseConst::Initialize();
	// �萔�̃��[�h�i�{���̎g�����Ƃ͈Ⴄ���A����͂���ł����j
	BaseConst::Loading();


	// �C���v�b�g�̏�����
	BaseInput::Initialize();
	// �G�t�F�N�g�}�l�[�W���[�̏�����
	BaseEffectManager::Initialize();

	// �X�N���[�����W��������
	BaseDraw::SetScreenPosition({ 0,1080 });

	// ���o�p�ϐ�
	easingT = 0;
	width = 0;
	// �X�L�b�v
	skipPosition[0] = {
		BaseConst::kWindowWidth - 100.0f,
		BaseConst::kWindowHeight - 100.0f
	};
	// A �{�^��
	skipPosition[1] = {
		BaseConst::kWindowWidth - 200.0f,
		BaseConst::kWindowHeight - 100.0f
	};
	// SPACE �L�[
	skipPosition[2] = {
		BaseConst::kWindowWidth - 430.0f,
		BaseConst::kWindowHeight - 100.0f
	};
	// ���o�X�L�b�v�p�ϐ�
	longPressedFrame = 0;

	// �����̏�����
	srand(time(nullptr));
}

// �X�V
void MyBase::Update() {
	BaseInput::Update();

	// �f�o�b�O�p
	// �萔�̃z�b�g�����[�h
	if (BaseInput::GetKeyboardState(DIK_F1, Trigger)) {
		BaseConst::Loading();
	}
	if (BaseInput::GetKeyboardState(DIK_RALT, Press) && BaseInput::GetKeyboardState(DIK_RETURN, Trigger)) {
		// �t���X�N���[�����[�h�؂�ւ�
		BaseDraw::ChangeFullScreen();
	}

	BaseEffectManager::Update();


	// ���o���n�܂����獕����\��
	if (PublicFlag::kisStaging) {
		easingT += 1.0f / 60.0f;
		if (easingT > 0.5f) {
			easingT = 0.5f;
		}
		width = BaseDraw::Ease_Out(easingT, 0, BaseConst::kWindowWidth, 0.5f);

		// �X�L�b�v�p�̏���
		if (BaseInput::GetKeyboardState(DIK_SPACE, Press)) {
			longPressedFrame++;

			if (longPressedFrame > 60) {
				PublicFlag::kisStaging = false;
				longPressedFrame = 0;
			}
		}
		else {
			if (longPressedFrame > 0) {
				longPressedFrame--;
			}
		}
	}
	else {
		easingT -= 1.0f / 60.0f;
		if (easingT < 0) {
			easingT = 0;
		}
		width = BaseDraw::Ease_In(easingT, 0, BaseConst::kWindowWidth, 0.5f);
	}
}

// �`��
void MyBase::Draw() {
	BaseEffectManager::Draw();
	BaseInput::Draw();


	// �����`��
	Novice::DrawBox(0, 0, width, 100, 0, BLACK, kFillModeSolid);
	Novice::DrawBox(BaseConst::kWindowWidth - width, BaseConst::kWindowHeight - 100, width, 100, 0, BLACK, kFillModeSolid);

	// �X�L�b�v�{�^���̕`��
	if (PublicFlag::kisStaging) {

		// �X�L�b�v
		Novice::DrawSpriteRect(
			skipPosition[0].x, skipPosition[0].y, 0, 0, 100, 100,
			BaseTexture::kUserInterfaceSkip[0], 1.0f, 1.0f, 0.0f, WHITE
		);
		Novice::DrawSpriteRect(
			skipPosition[0].x, skipPosition[0].y, 0, 0, 100 / 60.0f * longPressedFrame, 100,
			BaseTexture::kUserInterfaceSkip[1], 100 / 60.0f * longPressedFrame / 100.0f, 1.0f, 0.0f, WHITE
		);
		// A �{�^��
		if (BaseInput::GetControllerState(kControllerButtonA, Press)) {
			Novice::DrawSpriteRect(
				skipPosition[1].x, skipPosition[1].y, 0, 0, 100, 100,
				BaseTexture::kUserInterfaceA[1], 1.0f, 1.0f, 0.0f, WHITE
			);
		}
		else {
			Novice::DrawSpriteRect(
				skipPosition[1].x, skipPosition[1].y, 0, 0, 100, 100,
				BaseTexture::kUserInterfaceA[0], 1.0f, 1.0f, 0.0f, WHITE
			);
		}
		// Space �{�^��
		if (BaseInput::GetKeyboardState(DIK_SPACE, Press)) {
			Novice::DrawSpriteRect(
				skipPosition[2].x, skipPosition[2].y, 0, 0, 256, 100,
				BaseTexture::kUserInterfaceSpace[1], 1.0f, 1.0f, 0.0f, WHITE
			);
		}
		else {
			Novice::DrawSpriteRect(
				skipPosition[2].x, skipPosition[2].y, 0, 0, 256, 100,
				BaseTexture::kUserInterfaceSpace[0], 1.0f, 1.0f, 0.0f, WHITE
			);
		}/*
		Novice::DrawSpriteRect(
			skipPosition[2].x, skipPosition[2].y, 0, 0, 256, 100,
			BaseTexture::kUserInterfaceSpace[0], 1.0f, 1.0f, 0.0f, WHITE
		);
		Novice::DrawSpriteRect(
			skipPosition[2].x, skipPosition[2].y, 0, 0, 256 / 60.0f * longPressedFrame, 100,
			BaseTexture::kUserInterfaceSpace[1], 256 / 60.0f * longPressedFrame / 256.0f, 1.0f, 0.0f, WHITE
		);*/
	}
}


// ���o�p�ϐ�
float MyBase::easingT;
float MyBase::width;
Point MyBase::skipPosition[3];

// ���o�X�L�b�v�p�ϐ�
int MyBase::longPressedFrame;