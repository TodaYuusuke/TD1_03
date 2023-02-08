#include "MyBase/Resource/BaseAudio.h"

// ������
void BaseAudio::Initialize() {
	LoadingPercent = 0;
	isLoadingComplete = false;

	InitializeVolume();
}


// BGM��SE��volume�������ݒ�ɖ߂�
void BaseAudio::InitializeVolume() {
	BGMvolume = 0.3f;
	SEvolume = 0.5f;
}


// ���[�h�֐�
// �Ԃ�l�F���[�h�����������ꍇ��true
// �����F����
// �I�[�f�B�I�̃��[�h��100�����ōs���B�S�Ẵ��[�h����������܂ŌĂяo������i����́��͎������Ȃ��A���[�h���邾���j
bool BaseAudio::Loading() {

#pragma region BGM

	// �`���[�g���A��BGM
	kBGMTutorial = Novice::LoadAudio("./Resources/Audio/BGM/Tutorial.mp3");

	// ���{�X��BGM
	//kBGMMiniBoss = Novice::LoadAudio("./Resources/Audio/BGM/Tutorial.mp3");

	// �{�X��BGM
	kBGMBoss = Novice::LoadAudio("./Resources/Audio/BGM/Boss.mp3");
	// �U���`�����X����BG�l
	kBGMChance = Novice::LoadAudio("./Resources/Audio/BGM/Chance.wav");

#pragma endregion


#pragma region �{�X

	// �{�X���J����
	kBossOpen = Novice::LoadAudio("./Resources/Audio/Boss/kBossOpen.wav");

	// ���鉹
	kBossClose = Novice::LoadAudio("./Resources/Audio/Boss/kBossClose.mp3");

	// ���K��
	kBossScream = Novice::LoadAudio("./Resources/Audio/Boss/kBossScream.wav");

	// �ːi���鉹
	kBossRush = Novice::LoadAudio("./Resources/Audio/Boss/kBossRush.mp3");

	// �e�W�J��
	kBossPickGun = Novice::LoadAudio("./Resources/Audio/Boss/kBossPickGun.wav");
	// �ˌ���
	kBossShot = Novice::LoadAudio("./Resources/Audio/Boss/kBossShot.wav");

	// �u���[�h�W�J��
	kBossDeployBlade = Novice::LoadAudio("./Resources/Audio/Boss/kBossDeployBlade.wav");
	// �a����
	kBossSlash = Novice::LoadAudio("./Resources/Audio/Boss/kBossSlash.wav");

	// �ǂɂԂ��������̉�
	kBossStrike = Novice::LoadAudio("./Resources/Audio/Boss/kBossStrike.mp3");

	// �ċN����
	kBossReboot = Novice::LoadAudio("./Resources/Audio/Boss/kBossReboot.wav");

	// �{�X�̃`���[�W��
	kBossCharge = Novice::LoadAudio("./Resources/Audio/Boss/kBossCharge.mp3");

	// �U����
	kBossVibration = Novice::LoadAudio("./Resources/Audio/Boss/kBossVib.wav");

	// �n�艹
	kBossRumbleEarth = Novice::LoadAudio("./Resources/Audio/Boss/kBossRumbleEarth.mp3");

	// �_���[�W��
	kBossDamage = Novice::LoadAudio("./Resources/Audio/Boss/kBossDamage.mp3");

	// �{�X�����E�Ɉ��������鉹
	kBossPull = Novice::LoadAudio("./Resources/Audio/Boss/kBossPull.mp3");
	// �{�X����_�����炷���̉�
	kBossHardOpen = Novice::LoadAudio("./Resources/Audio/Boss/kBossHardOpen.mp3");

	// �{�X�̃R�A�Ɗj���������鉹
	kBossSeparateCore = Novice::LoadAudio("./Resources/Audio/Boss/kBossSeparateCore.mp3");

	// �{�X���������鉹
	kBossDelete = Novice::LoadAudio("./Resources/Audio/Boss/kBossDelete.mp3");

#pragma endregion

#pragma region Player

	// �W�����v
	kPlayerJump = Novice::LoadAudio("./Resources/Audio/Player/Jump.mp3");
	// ��_���[�W
	kPlayerDamage = Novice::LoadAudio("./Resources/Audio/Player/Damage.mp3");
	// �ˌ�
	kPlayerShoot = Novice::LoadAudio("./Resources/Audio/Player/Shoot.mp3");
	// �r�
	kPlayerEjection = Novice::LoadAudio("./Resources/Audio/Player/Ejection.mp3");

#pragma endregion

#pragma region Wire

	// ���C���[���q�b�g
	kWireHit = Novice::LoadAudio("./Resources/Audio/Wire/Hit.mp3");
	// ���C���[���؂��
	kWireCut = Novice::LoadAudio("./Resources/Audio/Wire/Cut.mp3");

#pragma endregion

	return true;
}


// ���[�h�����擾����֐�
// �Ԃ�l�F���݂̃��[�h���i���j
// �����F����
// ���݂̃��[�h�󋵂��擾����֐��B
int BaseAudio::GetLoadingPercent() {
	return LoadingPercent;
}


//////////////////////////////////
/* - static�����o�ϐ��̎��Ԃ�錾 - */
//////////////////////////////////

// ���݂̃��[�h��
int BaseAudio::LoadingPercent;
// ���[�h������������
bool BaseAudio::isLoadingComplete;
// BGM�n�̉���
float BaseAudio::BGMvolume;
// SE�n�̉���
float BaseAudio::SEvolume;

#pragma region BGM

// �`���[�g���A��BGM
int BaseAudio::kBGMTutorial;

// ���{�X��BGM
int BaseAudio::kBGMMiniBoss;

// �{�X��BGM
int BaseAudio::kBGMBoss;
// �U���`�����X����BG�l
int BaseAudio::kBGMChance;

#pragma endregion


#pragma region �{�X

// �J����
int BaseAudio::kBossOpen;

// ���鉹
int BaseAudio::kBossClose;

// ���K��
int BaseAudio::kBossScream;

// �ːi���鉹
int BaseAudio::kBossRush;

// �u���[�h�W�J��
int BaseAudio::kBossDeployBlade;
// �u���[�h�a����
int BaseAudio::kBossSlash;

// �ǂɂԂ��������̉�
int BaseAudio::kBossStrike;

// �e�����o����
int BaseAudio::kBossPickGun;
// �ˌ���
int BaseAudio::kBossShot;

// �{�X�̍ċN����
int BaseAudio::kBossReboot;

// �{�X�̃`���[�W��
int BaseAudio::kBossCharge;

// �{�X�̐U����
int BaseAudio::kBossVibration;

// �{�X�̒n�艹
int BaseAudio::kBossRumbleEarth;

// �{�X�Ƀ_���[�W�����������̉�
int BaseAudio::kBossDamage;

// �{�X�����E�Ɉ��������鉹
int BaseAudio::kBossPull;
// �{�X����_�����炷���̉�
int BaseAudio::kBossHardOpen;

// �{�X�̃R�A�Ɗj���������鉹
int BaseAudio::kBossSeparateCore;

// �{�X���������鉹
int BaseAudio::kBossDelete;

#pragma endregion

#pragma region Player

// �W�����v
int BaseAudio::kPlayerJump;
// ��_���[�W
int BaseAudio::kPlayerDamage;
// �ˌ�
int BaseAudio::kPlayerShoot;
// �r�
int BaseAudio::kPlayerEjection;

#pragma endregion

#pragma region Wire

// ���C���[���q�b�g
int BaseAudio::kWireHit;
// ���C���[���؂��
int BaseAudio::kWireCut;

#pragma endregion