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

#pragma region �}�b�v

	// �}�b�v�`�b�v�T���v��
	// 0 ... �g�Ȃ�
	// 1,2,3,4 ... ��,�E,��,��
	// 5,6,7,8 ... �E��,�E��,����,����
	// 9,10,11,12 ... ���ȊO,���ȊO,��ȊO,�E�ȊO
	// 13 ... �S��
	static int kTextureMapChipSample[];
	static const int kTextureMapChipSampleSize = 14;

	// �������鏰
	static int kTextureMapChipFloor;

#pragma endregion

#pragma region �{�X

	// �{�X�̊j
	static int kBossCore;

	// �{�X�̃J�o�[
	static int kBossRCover;
	static int kBossLCover;

	// �t�b�N
	static int kBossHook;

#pragma endregion

#pragma region ���̑�

	// �u���b�N
	static int kBlockTexture;

#pragma endregion
};