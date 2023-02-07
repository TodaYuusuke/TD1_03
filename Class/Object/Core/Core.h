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


	// �����蔻��֘A

	// �I�u�W�F�N�g�ɑ΂��铖���蔻����`�F�b�N����֐�
	// �Ԃ�l�F�q�b�g���Ă����ꍇ ... true
	// �����F�`�F�b�N����Point
	bool CheckHitBox(Point hitPosition) override;

private:

	int pullCount;

};