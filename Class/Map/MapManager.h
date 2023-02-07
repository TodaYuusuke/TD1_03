#pragma once
#include "MyBase/MyBase.h"

class Map;

// �}�b�v���Ǘ�����N���X

// �}�b�v�̓ǂݍ��݂̎d�l��A���̃N���X���̏����͂��ׂăX�N���[�����W�ōs���A�O�ɏo���ꍇ�͕K�����[���h���W�ŕԂ�����

class MapManager {
public: // �����o�֐�

	// �R���X�g���N�^
	MapManager();
	// �f�X�g���N�^
	~MapManager();


	// ������
	static void TutorialInitialize();
	static void BossInitialize();
	// �X�V
	static void Update();
	// �`��
	static void Draw();

	/// <summary>
	/// �w�肵�����W���}�b�v�Ƀq�b�g���Ă��邩�ǂ���
	/// </summary>
	/// <param name="hitPosition �����蔻����m�F������W"></param>
	/// <param name="isBlock �q�b�g����̂�Block���ǂ���"></param>
	/// <returns>�q�b�g���Ă����ꍇ ... true�A�q�b�g���Ă��Ȃ������ꍇ ... false</returns>
	static bool CheckHitBox(Point hitPosition, bool isBlock);

	// ���݃{�X�X�e�[�W�Ȃ̂����󂯎��֐�
	static bool GetisBoss() { return isBoss; }

private: // �֐�

	// �}�b�v�`�b�v�̌`�����肷��֐�
	static int GetMapChipType(int y, int x);

private: // �����o�ϐ�

	// ���݃{�X�}�b�v�̏������s���Ă���̂��t���O
	static bool isBoss;

	// �`���[�g���A���}�b�v�̔z��
	static Map* tutorialMap[35][500];
	// �{�X�}�b�v�̔z��
	static Map* bossMap[35][75];
};