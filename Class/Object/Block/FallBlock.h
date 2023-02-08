#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/Object.h"

// ���C���[���h����u���b�N

class FallBlock :
	public Object {
public: // �����o�֐�

	// �R���X�g���N�^
	FallBlock(Point centerPosition, bool isCanStub);
	// �f�X�g���N�^
	~FallBlock();

	// ������
	void SuccessorInitialize() override;
	// �X�V
	void SuccessorUpdate() override;
	// �`��
	void Draw() override;
	// �^�C�v�擾
	ObjectType GetType() override;

private: // �����o�ϐ�
	
	// ���C���[���Ђ��������邩
	bool isCanStub;

	// ��������Ă���A������܂ł̎���
	int vanishFlame;
};