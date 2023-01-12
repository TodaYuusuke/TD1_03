#pragma once
#include "MyBase/Include/MyBase.h"
#include "Class/Include/Object/Object.h"
//#include "Class/Include/Wire/WireManager.h"


// �����܂ł��Ȃ��v���C���[


class Player :
	public Object {
public: // �����o�֐�

	// �R���X�g���N�^
	Player(Point centerPosition);
	// �f�X�g���N�^
	~Player();

	// ������
	void SuccessorInitialize() override;
	// �X�V
	void SuccessorUpdate() override;
	// �`��
	void Draw() override;

	ObjectType GetType() override;

private: // �֐�

	// �ǂ����Update()�Ŗ��t���[���Ăяo������

	// �ړ��֘A
	void Move();
	// ���C���[���ˏo���铮��
	void ShotWire();

private: // �����o�ϐ�

	const static int kPlayerSpeedX = 4;
	const static int kPlayerSpeedY = 20;

	// �}�E�X���W
	Point ReticlePosition;

};