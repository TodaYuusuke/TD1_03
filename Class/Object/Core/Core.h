#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/Object.h"

// ���C���[���h����ꏊ

class Core :
	public Object {
public: // �����o�֐�

	// �R���X�g���N�^
	Core(Point centerPosition, Point size);
	// �f�X�g���N�^
	~Core();

	// ������
	void SuccessorInitialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;
	// �^�C�v�擾
	ObjectType GetType() override;

private:

	int pullCount;

};