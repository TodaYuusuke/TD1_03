#pragma once
#include "MyBase/MyBase.h"
#include "Class/PublicFlag/PublicFlag.h"

enum MapChipType {
	// �󔒁i�����Ȃ��j
	kTypeAir,
	// �ʏ�}�X
	kTypeNormal,
	// �w�i�}�X�i�����蔻�薳���j
	kTypeWall,
	// ����}�X
	kTypeWeak,
};

class Map {
public: // �����o�֐�

	// �R���X�g���N�^
	Map();
	// �f�X�g���N�^
	~Map();

	// ������
	void Initialize(MapChipType type);
	// �X�V
	void Update();
	// �`��
	void Draw(Point drawPosition, int drawImageNum);

	/// <summary>
	/// �w�肵�����W���}�b�v�Ƀq�b�g���Ă��邩�ǂ���
	/// </summary>
	/// <param name="hitPosition �����蔻����m�F������W"></param>
	/// <param name="isBlock �q�b�g����̂�Block���ǂ���"></param>
	/// <returns></returns>
	bool CheckHitBox(Point hitPosition, bool isBlock);

	// �p�u���b�N�ϐ�
	MapChipType type;
};