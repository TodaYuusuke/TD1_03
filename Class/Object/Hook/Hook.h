#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/Object.h"

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

	// �����蔻��֘A

	// �I�u�W�F�N�g�ɑ΂��铖���蔻����`�F�b�N����֐�
	// �Ԃ�l�F�q�b�g���Ă����ꍇ ... true
	// �����F�`�F�b�N����Point
	bool CheckHitBox(Point hitPosition) override;

private:

	int pullCount;

};