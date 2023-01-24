#pragma once
#include "MyBase/Include/MyBase.h"
#include "Class/Include/Object/Object.h"

// ���C���[���h����ꏊ

class Hook :
	public Object {
public: // �����o�֐�

	// �R���X�g���N�^
	Hook(Point centerPosition, Point size);
	// �f�X�g���N�^
	~Hook();

	// ������
	void SuccessorInitialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;
	// �^�C�v�擾
	ObjectType GetType() override;

};