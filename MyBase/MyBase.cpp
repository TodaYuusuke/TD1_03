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

}

// �`��
void MyBase::Draw(){
	BaseEffectManager::Draw();
	BaseInput::Draw();

	// ���o���n�܂����獕����\��
	if (PublicFlag::kisStaging) {
		easingT += 1.0f / 60.0f;
		if (easingT > 0.5f) {
			easingT = 0.5f;
		}
		width = BaseDraw::Ease_Out(easingT, 0, BaseConst::kWindowWidth, 0.5f);
	}
	else {
		easingT -= 1.0f / 60.0f;
		if (easingT < 0) {
			easingT = 0;
		}
		width = BaseDraw::Ease_In(easingT, 0, BaseConst::kWindowWidth, 0.5f);
	}


	Novice::DrawBox(0, 0, width, 100, 0, BLACK, kFillModeSolid);
	Novice::DrawBox(BaseConst::kWindowWidth - width, BaseConst::kWindowHeight - 100, width, 100, 0, BLACK, kFillModeSolid);
}


// ���o�p�ϐ�
float MyBase::easingT;
float MyBase::width;