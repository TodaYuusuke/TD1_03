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

#pragma region �w�i

	// �w�i�t���[��
	kBackGround[0] = Novice::LoadTexture("./Resources/Texture/BackGround/back_ground2.png");
	kBackGround[1] = Novice::LoadTexture("./Resources/Texture/BackGround/back_ground1.png");
	kBackGround[2] = Novice::LoadTexture("./Resources/Texture/BackGround/back_ground0.png");

#pragma endregion

#pragma region �}�b�v

	// �}�b�v�`�b�v�T���v��
	kTextureMapChip[0] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip1.png");
	kTextureMapChip[1] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip2.png");
	kTextureMapChip[2] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip3.png");
	kTextureMapChip[3] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip4.png");
	kTextureMapChip[4] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip5.png");
	kTextureMapChip[5] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip6.png");
	kTextureMapChip[6] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip7.png");
	kTextureMapChip[7] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip8.png");
	kTextureMapChip[8] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip9.png");
	kTextureMapChip[9] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip10.png");
	kTextureMapChip[10] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip11.png");
	kTextureMapChip[11] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip12.png");
	kTextureMapChip[12] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip13.png");
	kTextureMapChip[13] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip14.png");
	// �q�r
	kTextureMapChipWeak = Novice::LoadTexture("./Resources/Texture/MapChip/Weak.png");

#pragma endregion

#pragma region �{�X

	// �{�X�̊j
	kBossCore = Novice::LoadTexture("./Resources/Texture/Boss/Kernel.png");

	// �{�X�̃J�o�[
	kBossRCover = Novice::LoadTexture("./Resources/Texture/Boss/RCover.png");
	kBossLCover = Novice::LoadTexture("./Resources/Texture/Boss/LCover.png");

	// �{�X�̃t�b�N
	kBossLHook = Novice::LoadTexture("./Resources/Texture/Boss/LHook.png");
	kBossRHook = Novice::LoadTexture("./Resources/Texture/Boss/RHook.png");

	// �{�X�̕���
	kBossBlade = Novice::LoadTexture("./Resources/Texture/Boss/Blade.png");
	kBossGun = Novice::LoadTexture("./Resources/Texture/Boss/Gun.png");

	// �{�X�̒e
	kBossBullet = Novice::LoadTexture("./Resources/Texture/Boss/Bullet.png");

#pragma endregion

#pragma region UI

	kUserInterfaceA[0] = Novice::LoadTexture("./Resources/Texture/UI/A0.png");
	kUserInterfaceA[1] = Novice::LoadTexture("./Resources/Texture/UI/A1.png");
	
	kUserInterfaceSpace[0] = Novice::LoadTexture("./Resources/Texture/UI/Space0.png");
	kUserInterfaceSpace[1] = Novice::LoadTexture("./Resources/Texture/UI/Space1.png");
	
	kUserInterfaceSkip[0] = Novice::LoadTexture("./Resources/Texture/UI/Skip0.png");
	kUserInterfaceSkip[1] = Novice::LoadTexture("./Resources/Texture/UI/Skip1.png");

	kUserInterfaceTitle[0] = Novice::LoadTexture("./Resources/Texture/UI/TitleSelect.png");

	kUserInterfaceGameOver = Novice::LoadTexture("./Resources/Texture/UI/GameOver.png");

#pragma endregion

#pragma region �v���C���[

	// �n�[�g
	kPlayerHeart[0] = Novice::LoadTexture("./Resources/Texture/Player/HeartFull.png");
	kPlayerHeart[1] = Novice::LoadTexture("./Resources/Texture/Player/HeartHalf.png");

	// ��
	// �A�C�h��
	kLPlayerIdle = Novice::LoadTexture("./Resources/Texture/Player/Left/L_chara_idle.png");
	// ����
	kLPlayerRun[0] = Novice::LoadTexture("./Resources/Texture/Player/Left/L_chara_dash0.png");
	kLPlayerRun[1] = Novice::LoadTexture("./Resources/Texture/Player/Left/L_chara_dash1.png");
	// �W�����v
	kLPlayerJump[0] = Novice::LoadTexture("./Resources/Texture/Player/Left/L_chara_jump0.png");
	kLPlayerJump[1] = Novice::LoadTexture("./Resources/Texture/Player/Left/L_chara_jump1.png");
	kLPlayerJump[2] = Novice::LoadTexture("./Resources/Texture/Player/Left/L_chara_jump2.png");
	kLPlayerJump[3] = Novice::LoadTexture("./Resources/Texture/Player/Left/L_chara_jump3.png");
	// ���C���ˏo
	kLPlayerShot = Novice::LoadTexture("./Resources/Texture/Player/Left/L_chara_shot.png");
	// ���C��������
	kLPlayerPull = Novice::LoadTexture("./Resources/Texture/Player/Left/L_chara_pull.png");

	// �E
	// �A�C�h��
	kRPlayerIdle = Novice::LoadTexture("./Resources/Texture/Player/Right/R_chara_idle.png");
	// ����
	kRPlayerRun[0] = Novice::LoadTexture("./Resources/Texture/Player/Right/R_chara_dash0.png");
	kRPlayerRun[1] = Novice::LoadTexture("./Resources/Texture/Player/Right/R_chara_dash1.png");
	// �W�����v
	kRPlayerJump[0] = Novice::LoadTexture("./Resources/Texture/Player/Right/R_chara_jump0.png");
	kRPlayerJump[1] = Novice::LoadTexture("./Resources/Texture/Player/Right/R_chara_jump1.png");
	kRPlayerJump[2] = Novice::LoadTexture("./Resources/Texture/Player/Right/R_chara_jump2.png");
	kRPlayerJump[3] = Novice::LoadTexture("./Resources/Texture/Player/Right/R_chara_jump3.png");
	// ���C���ˏo
	kRPlayerShot = Novice::LoadTexture("./Resources/Texture/Player/Right/R_chara_shot.png");
	// ���C��������
	kRPlayerPull = Novice::LoadTexture("./Resources/Texture/Player/Right/R_chara_pull.png");

#pragma endregion

#pragma region ���̑�

	// �u���b�N
	kBlockTexture = Novice::LoadTexture("./Resources/Texture/Block/Block.png");
	// �u���b�N�̔j��
	kBlockScrap[0] = Novice::LoadTexture("./Resources/Texture/Block/Scrap0.png");
	kBlockScrap[1] = Novice::LoadTexture("./Resources/Texture/Block/Scrap1.png");
	kBlockScrap[2] = Novice::LoadTexture("./Resources/Texture/Block/Scrap2.png");
	kBlockScrap[3] = Novice::LoadTexture("./Resources/Texture/Block/Scrap3.png");
	kBlockScrap[4] = Novice::LoadTexture("./Resources/Texture/Block/Scrap4.png");
	kBlockScrap[5] = Novice::LoadTexture("./Resources/Texture/Block/Scrap5.png");
	kBlockScrap[6] = Novice::LoadTexture("./Resources/Texture/Block/Scrap6.png");
	kBlockScrap[7] = Novice::LoadTexture("./Resources/Texture/Block/Scrap7.png");
	kBlockScrap[8] = Novice::LoadTexture("./Resources/Texture/Block/Scrap8.png");
	kBlockScrap[9] = Novice::LoadTexture("./Resources/Texture/Block/Scrap9.png");
	kBlockScrap[10] = Novice::LoadTexture("./Resources/Texture/Block/Scrap10.png");
	kBlockScrap[11] = Novice::LoadTexture("./Resources/Texture/Block/Scrap11.png");

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

#pragma region �w�i

// �w�i
int BaseTexture::kBackGround[3];

#pragma endregion

#pragma region �}�b�v

// �}�b�v�`�b�v
int BaseTexture::kTextureMapChip[kTextureMapChipSize];
// �q�r
int BaseTexture::kTextureMapChipWeak;

#pragma endregion


#pragma region �{�X

// �{�X�̊j
int BaseTexture::kBossCore;

// �{�X�̃J�o�[
int BaseTexture::kBossRCover;
int BaseTexture::kBossLCover;

int BaseTexture::kBossLHook;
int BaseTexture::kBossRHook;

// ����
int BaseTexture::kBossBlade;
int BaseTexture::kBossGun;

// �e
int BaseTexture::kBossBullet;

#pragma endregion

#pragma region UI

int BaseTexture::kUserInterfaceA[2];
int BaseTexture::kUserInterfaceSpace[2];
int BaseTexture::kUserInterfaceSkip[2];

int BaseTexture:: kUserInterfaceTitle[2];
int BaseTexture:: kUserInterfaceGameOver;

#pragma endregion

#pragma region �v���C���[

// �n�[�g
int BaseTexture::kPlayerHeart[2];

// ��
// �A�C�h��
int BaseTexture::kLPlayerIdle;
// ����
int BaseTexture::kLPlayerRun[2];
// �W�����v
int BaseTexture::kLPlayerJump[4];
// ���C���ˏo
int BaseTexture::kLPlayerShot;
// ���C��������
int BaseTexture::kLPlayerPull;

// �E
// �A�C�h��
int BaseTexture::kRPlayerIdle;
// ����
int BaseTexture::kRPlayerRun[2];
// �W�����v
int BaseTexture::kRPlayerJump[4];
// ���C���ˏo
int BaseTexture::kRPlayerShot;
// ���C��������
int BaseTexture::kRPlayerPull;

#pragma endregion

#pragma region ���̑�

// �u���b�N
int BaseTexture::kBlockTexture;
// �u���b�N�̔j��
int BaseTexture::kBlockScrap[kBlockScrapAmount];

#pragma endregion