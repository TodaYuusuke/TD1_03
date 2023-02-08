#pragma once
#include <Novice.h>


///////////////////////////////////////////////////////
/* - �Q�[�����Ŏg���S�Ẵe�N�X�`���t�@�C�����Ǘ�����N���X - */
///////////////////////////////////////////////////////


class BaseTexture
{

public: // �����o�֐�

	// ������
	static void Initialize();


	// ���[�h�֐�
	// �Ԃ�l�F���[�h�����������ꍇ��true
	// �����F����
	// �e�N�X�`���̃��[�h��100�����ōs���B�S�Ẵ��[�h����������܂ŌĂяo������i����́��͎������Ȃ��A���[�h���邾���j
	static bool Loading();

	// ���[�h�����擾����֐�
	// �Ԃ�l�F���݂̃��[�h���i���j
	// �����F����
	// ���݂̃��[�h�󋵂��擾����֐��B
	static int GetLoadingPercent();


private: // �����o�ϐ�

	// ���݂̃��[�h��
	static int LoadingPercent;
	// ���[�h������������
	static bool isLoadingComplete;


public: // �ÓI�ȃe�N�X�`���̕ϐ�

	// �f�o�b�O�p�e�N�X�`��
	static int kDebugTexture;

#pragma region �w�i

	// �w�i
	static int kBackGround[3];

#pragma endregion

#pragma region �}�b�v

	// �}�b�v�`�b�v�T���v��
	// 0 ... �g�Ȃ�
	// 1,2,3,4 ... ��,�E,��,��
	// 5,6,7,8 ... �E��,�E��,����,����
	// 9,10,11,12 ... ���ȊO,���ȊO,��ȊO,�E�ȊO
	// 13 ... �S��
	static const int kTextureMapChipSize = 14;
	static int kTextureMapChip[kTextureMapChipSize];
	// �q�r
	static int kTextureMapChipWeak;

#pragma endregion

#pragma region �{�X

	// ���{�X�摜
	static int kMiddleBoss;

	// ���{�X����摜
	static int kMiddleBossBlade;

	// �{�X�̊j
	static int kBossCore;

	// �{�X�̃J�o�[
	static int kBossRCover;
	static int kBossLCover;

	// �t�b�N
	static int kBossLHook;
	static int kBossRHook;

	// ����
	static int kBossBlade;
	static int kBossGun;

	// �{�X�̔��˂���e
	static int kBossBullet;

#pragma endregion

#pragma region UI

	// A �{�^��
	static int kUserInterfaceA[2];
	// Space
	static int kUserInterfaceSpace[2];
	// Skip
	static int kUserInterfaceSkip[2];

	// Title
	// �Z���N�g
	// ���S
	static int kUserInterfaceTitle[2];

	// GameOver
	static int kUserInterfaceGameOver;

	// ��
	static int kNumbers[6];

#pragma endregion

#pragma region �v���C���[

	// �n�[�g
	static int kPlayerHeart[2];

	// ��
	// �A�C�h��
	static int kLPlayerIdle;
	// ����
	static int kLPlayerRun[2];
	// �W�����v
	static int kLPlayerJump[4];
	// ���C���ˏo
	static int kLPlayerShot;
	// ���C��������
	static int kLPlayerPull;

	// �E
	// �A�C�h��
	static int kRPlayerIdle;
	// ����
	static int kRPlayerRun[2];
	// �W�����v
	static int kRPlayerJump[4];
	// ���C���ˏo
	static int kRPlayerShot;
	// ���C��������
	static int kRPlayerPull;

#pragma endregion

#pragma region �G��

	// ���D
	static int kEnemyBalloon[4];
	static int kEnemyBalloonDead[6];
	// �����̕��D
	static int kEnemyIronBalloon[4];
	static int kEnemyIronBalloonDead[6];

#pragma endregion

#pragma region �`���[�g���A���p�l�I��

	// �W�����v
	static int kTutorialJump[2];
	// ���C���[����
	static int kTutorialWire[2];
	// ������
	static int kTutorialAttract[2];
	// �����E��
	static int kTutorialShot[2];
	// �񔭖ڂ̔���
	static int kTutorialSecondShot[4];

#pragma endregion

#pragma region ���̑�

	// �u���b�N
	static int kBlockTexture;
	// �u���b�N�̔j��
	const static int kBlockScrapAmount = 12;
	static int kBlockScrap[12];

	// �p�C�v
	static int kPipe;

#pragma endregion
};