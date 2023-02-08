#include "MyBase/Resource/BaseConst.h"

// ������
void BaseConst::Initialize() {
	LoadingPercent = 0;
	isLoadingComplete = false;
}


// ���[�h�֐�
// �Ԃ�l�F���[�h�����������ꍇ��true
// �����F����
// �萔�̃��[�h��100�����ōs���B�S�Ẵ��[�h����������܂ŌĂяo������i����́��͎������Ȃ��A���[�h���邾���j
bool BaseConst::Loading() {

	// �`���[�g���A���X�e�[�W���[�h
	//std::vector<std::string> map;
	std::ifstream tutorialMapifs("./Resources/Const/TutorialStage.csv");
	std::string line;

	int y = 0;
	while (getline(tutorialMapifs, line)) {

		std::vector<std::string> strvec = split(line, ',');

		for (int x = 0; x < strvec.size(); x++) {
			kTutorialStageData[y][x] = stoi(strvec.at(x));
		}

		y++;
	}

	// �{�X�X�e�[�W���[�h
	std::ifstream bossMapifs("./Resources/Const/BossStage.csv");

	y = 0;

	while (getline(bossMapifs, line)) {

		std::vector<std::string> strvec = split(line, ',');

		for (int x = 0; x < strvec.size(); x++) {
			kBossStageData[y][x] = stoi(strvec.at(x));
		}

		y++;
	}

	// �v���C���[�̃A�j���[�V�������̕`��t���[����ݒ�
	kPlayerAnimationFlame[PlayerState::playerIdle] = 1;
	kPlayerAnimationFlame[PlayerState::playerRun] = 3;
	kPlayerAnimationFlame[PlayerState::playerJump] = 2;
	kPlayerAnimationFlame[PlayerState::playerRase] = 1;
	kPlayerAnimationFlame[PlayerState::playerFall] = 1;
	kPlayerAnimationFlame[PlayerState::playerLand] = 2;
	kPlayerAnimationFlame[PlayerState::playerShot] = 10;
	kPlayerAnimationFlame[PlayerState::playerPull] = 10;


	// �`���[�g���A���X�e�[�W�̐i�s�x�̖ڈ�
	kRespawnProgress[0].x = 112 * BaseConst::kMapChipSizeWidth;	// �����C���[
	kRespawnProgress[0].y = 3 * BaseConst::kMapChipSizeHeight + 50;
	kRespawnProgress[1].x = 206 * BaseConst::kMapChipSizeWidth;	// ���G���G
	kRespawnProgress[1].y = 3 * BaseConst::kMapChipSizeHeight + 50;
	kRespawnProgress[2].x = 383 * BaseConst::kMapChipSizeWidth;	// ���{�X�O
	kRespawnProgress[2].y = 29 * BaseConst::kMapChipSizeHeight + 50;
	kRespawnProgress[3].x = 458 * BaseConst::kMapChipSizeWidth;	// �G�����b�V���O
	kRespawnProgress[3].y = 3 * BaseConst::kMapChipSizeHeight + 50;
	
	kGimmickProgress[0] = 25 * BaseConst::kMapChipSizeWidth;	// �W�����v�`���[�g���A��
	kGimmickProgress[1] = 123 * BaseConst::kMapChipSizeWidth;	// ���C���[�`���[�g���A��
	kGimmickProgress[2] = 216 * BaseConst::kMapChipSizeWidth;	// �G�������A�`���[�g���A��
	kGimmickProgress[3] = 290 * BaseConst::kMapChipSizeWidth;	// �����~���Ă���
	kGimmickProgress[4] = 308 * BaseConst::kMapChipSizeWidth;	// �G������
	kGimmickProgress[5] = 388 * BaseConst::kMapChipSizeWidth;	// ���{�X����
	kGimmickProgress[6] = 473 * BaseConst::kMapChipSizeWidth;	// �G�����b�V���J�n


	return true;
}


// ���[�h�����擾����֐�
// �Ԃ�l�F���݂̃��[�h���i���j
// �����F����
// ���݂̃��[�h�󋵂��擾����֐��B
int BaseConst::GetLoadingPercent() {
	return LoadingPercent;
}


//////////////////////////////////
/* - static�����o�ϐ��̎��Ԃ�錾 - */
//////////////////////////////////

int BaseConst::LoadingPercent;
bool BaseConst::isLoadingComplete;


#pragma region �𑜓x

// �E�B���h�E�𑜓x�i�������j
int BaseConst::kWindowWidth = 1920;
// �E�B���h�E�𑜓x�i�c�����j
int BaseConst::kWindowHeight = 1080;

#pragma endregion

#pragma region �u���b�N

// �u���b�N��������܂ł̃t���[����
int BaseConst::kBlockVanishFlame = 1800;
// �u���b�N���_�ł��n�߂�t���[��
int BaseConst::kBlockBeVanish = 300;


#pragma endregion

#pragma region �v���C���[

// �v���C���[�̃T�C�Y
Point BaseConst::kPlayerSize = { 60,100 };

// �d�͉����x
float BaseConst::kPlayerGravitationalAcceleration = 9.8f / 30.0f;
// �S�̂̑��x����
float BaseConst::kPlayerVelocityLimit = 10.0f;

// �ړ� //

// ���s�ړ��̌��E���x
float BaseConst::kPlayerWalkVelocityLimit = 3.0f;

// �W�����v //

// �W�����v�̑��x
Point BaseConst::kPlayerJumpVelocity = { 0,9.8f };
// �W�����v�̃N�[���^�C��
int BaseConst::kPlayerJumpCoolTime = 40;

// �Ə� //

// �Ə��̍ő�˒�
int BaseConst::kPlayerReticleRange = 1500;

// �Ə��̃T�C�Y
int BaseConst::kPlayerReticleSize = 10;

// ����A�j���[�V���� 2
int BaseConst::kPlayerTextureRunNum = 2;

// �W�����v�A�j���[�V���� 4
int BaseConst::kPlayerTextureJumpNum = 4;

// �A�j���[�V�����Œ�o�߃t���[��
int BaseConst::kPlayerMaxAnimationFlame = 8;

// �A�j���[�V�������̕`��t���[��
int BaseConst::kPlayerAnimationFlame[PlayerState::kPlayerStateCount];

#pragma endregion

#pragma region ���C���[

// ���C���[�̒e��
float BaseConst::kWireSpeed = 40;

// ���C���[�̍ő�̒���
float BaseConst::kWireMaxLength = 1500.0f;
// ���C���[�̍ő呶�ݐ�
//int BaseConst::kWireMaxAmount = 3;

#pragma endregion

#pragma region �}�b�v

// �}�b�v�f�[�^
int BaseConst::kTutorialStageData[kTutorialStageSizeHeight][kTutorialStageSizeWidth];
int BaseConst::kBossStageData[kBossStageSizeHeight][kBossStageSizeWidth];

// �`���[�g���A���X�e�[�W�̐i�s�x�̖ڈ�
Point BaseConst::kRespawnProgress[4];
int BaseConst::kGimmickProgress[7];

#pragma endregion

#pragma region Scene

// ���炩���ߕ`�悷�銮���x
float BaseConst::kGameOverFirstValue = 0.2f;
float BaseConst::kGameOverFlame = (1 - BaseConst::kGameOverFirstValue) / (float)BaseConst::kGameOverMaxFlame;

// �u�^�C�g���֖߂�v�e����W
Point BaseConst::kGameOverTitleLeftTop = { 96,880 };
Point BaseConst::kGameOverTitleRightBottom = { 743,983 };

Point BaseConst::kGameOverRetryLeftTop = { 1210,880 };
Point BaseConst::kGameOverRetryRightBottom = { 1559,975 };

// �u�X�^�[�g�v�e����W
Point BaseConst::kTitletoPlayLeftTop = {1060,750};
Point BaseConst::kTitletoPlayRightBottom = { 1319,829 };
// �u�G���h�v�e����W
Point BaseConst::kTitletoEndLeftTop = { 1060,900 };
Point BaseConst::kTitletoEndRightBottom = {1249,978};

#pragma endregion