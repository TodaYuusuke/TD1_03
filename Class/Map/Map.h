#pragma once
#include "MyBase/MyBase.h"

enum MapChipType {
	// �󔒁i�����Ȃ��j
	kTypeAir,
	// �ʏ�}�X
	kTypeNormal,
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
	/// <returns></returns>
	bool CheckHitBox(Point hitPosition);

	// �p�u���b�N�ϐ�
	MapChipType type;
};