#pragma once
#include "MyBase/Include/MyBase.h"
#include "Class/Include/Object/Object.h"

// ���C���[���h����u���b�N

class Block :
	public Object {
public: // �����o�֐�

	// �R���X�g���N�^
	Block(Point centerPosition, Point size);
	// �f�X�g���N�^
	~Block();

	// ������
	void SuccessorInitialize() override;
	// �X�V
	void SuccessorUpdate() override;
	// �`��
	void Draw() override;
	// �^�C�v�擾
	ObjectType GetType() override;

};