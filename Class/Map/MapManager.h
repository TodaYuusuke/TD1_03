#pragma once
#include "MyBase/MyBase.h"

#include "Class/Map/Map.h"

// �}�b�v���Ǘ�����N���X

// �}�b�v�̓ǂݍ��݂̎d�l��A���̃N���X���̏����͂��ׂăX�N���[�����W�ōs���A�O�ɏo���ꍇ�͕K�����[���h���W�ŕԂ�����

class MapManager {
public: // �����o�֐�

	// �R���X�g���N�^
	MapManager();
	// �f�X�g���N�^
	~MapManager();


	// ������
	static void Initialize();
	// �X�V
	static void Update();
	// �`��
	static void Draw();

	/// <summary>
	/// �w�肵�����W���}�b�v�Ƀq�b�g���Ă��邩�ǂ���
	/// </summary>
	/// <param name="hitPosition �����蔻����m�F������W"></param>
	/// <returns>�q�b�g���Ă����ꍇ ... true�A�q�b�g���Ă��Ȃ������ꍇ ... false</returns>
	static bool CheckHitBox(Point hitPosition);

private: // �֐�

	// �}�b�v�`�b�v�̌`�����肷��֐�
	static int GetMapChipType(int y, int x);

private: // �����o�ϐ�

	// �}�b�v�̔z��
	static Map map[BaseConst::kBossStageSizeHeight][BaseConst::kBossStageSizeWidth];
};