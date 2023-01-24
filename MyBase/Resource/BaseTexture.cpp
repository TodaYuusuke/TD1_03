#include "MyBase/Resource/BaseTexture.h"

// ������
void BaseTexture::Initialize() {
	LoadingPercent = 0;
	isLoadingComplete = false;
}


// ���[�h�֐�
// �Ԃ�l�F���[�h�����������ꍇ��true
// �����F����
// �e�N�X�`���̃��[�h��100�����ōs���B�S�Ẵ��[�h����������܂ŌĂяo������i����́��͎������Ȃ��A���[�h���邾���j
bool BaseTexture::Loading() {

	kDebugTexture = Novice::LoadTexture("white1x1.png");

#pragma region �}�b�v

	// �}�b�v�`�b�v�T���v��
	kTextureMapChipSample[0] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample1.png");
	kTextureMapChipSample[1] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample2.png");
	kTextureMapChipSample[2] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample3.png");
	kTextureMapChipSample[3] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample4.png");
	kTextureMapChipSample[4] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample5.png");
	kTextureMapChipSample[5] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample6.png");
	kTextureMapChipSample[6] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample7.png");
	kTextureMapChipSample[7] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample8.png");
	kTextureMapChipSample[8] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample9.png");
	kTextureMapChipSample[9] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample10.png");
	kTextureMapChipSample[10] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample11.png");
	kTextureMapChipSample[11] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample12.png");
	kTextureMapChipSample[12] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample13.png");
	kTextureMapChipSample[13] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample14.png");

	// �������鏰
	kTextureMapChipFloor = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Floor.png");

#pragma endregion

#pragma region �{�X

	// �{�X�̊j
	kBossCore = Novice::LoadTexture("./Resources/Texture/Boss/Kernel.png");

	// �{�X�̃J�o�[
	kBossRCover = Novice::LoadTexture("./Resources/Texture/Boss/RCover.png");
	kBossLCover = Novice::LoadTexture("./Resources/Texture/Boss/LCover.png");

	// �{�X�̃t�b�N
	kBossHook = Novice::LoadTexture("./Resources/Texture/Boss/Hook.png");
#pragma endregion

	return true;
}


// ���[�h�����擾����֐�
// �Ԃ�l�F���݂̃��[�h���i���j
// �����F����
// ���݂̃��[�h�󋵂��擾����֐��B
int BaseTexture::GetLoadingPercent() {
	return LoadingPercent;
}


//////////////////////////////////
/* - static�����o�ϐ��̎��Ԃ�錾 - */
//////////////////////////////////

int BaseTexture::LoadingPercent;
bool BaseTexture::isLoadingComplete;


int BaseTexture::kDebugTexture;

#pragma region �}�b�v

int BaseTexture::kTextureMapChipSample[kTextureMapChipSampleSize];

// �������鏰
int BaseTexture::kTextureMapChipFloor;

#pragma endregion


#pragma region �{�X

// �{�X�̊j
int BaseTexture::kBossCore;

// �{�X�̃J�o�[
int BaseTexture::kBossRCover;
int BaseTexture::kBossLCover;

int BaseTexture::kBossHook;

#pragma endregion