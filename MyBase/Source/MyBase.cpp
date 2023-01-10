#include "Base/Include/Base.h"


// ������
void Base::Initialize() {

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


	// �����̏�����
	srand(time(nullptr));
}

// �X�V
void Base::Update() {
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
void Base::Draw(){
	BaseEffectManager::Draw();
	BaseInput::Draw();
}