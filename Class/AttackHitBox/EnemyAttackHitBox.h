#pragma once
#include "MyBase/MyBase.h"

// �{�X�̐������铖���蔻����Ǘ�����N���X

class EnemyAttackHitBox {
public: // �����o�֐�

	// ������
	static void Initialize();
	// �X�V
	static void Update();
	// �`��
	static void Draw();

	// �V���������蔻���ǉ�����֐��i�l�p�j
	// �����F
	// centerPosition ... �^�񒆂̍��W
	// width ... �q�b�g�{�b�N�X�̉����i����̓_����j
	// height ... �q�b�g�{�b�N�X�̏c���i����̓_����j
	// angle ... �q�b�g�Ώۂ̎l�p�̉�]�p�x
	// atk ... �_���[�W��
	static void MakeNewHitBox(Point centerPosition, float width, float height, float angle, float atk);

	// �V���������蔻���ǉ�����֐��i���̉~�j
	// �����F
	// centerPosition ... �^�񒆂̍��W
	// width ... �q�b�g�{�b�N�X�̉����i����̓_����j
	// height ... �q�b�g�{�b�N�X�̏c���i����̓_����j
	// angle ... �q�b�g�Ώۂ̎l�p�̉�]�p�x
	// atk ... �_���[�W��
	static void MakeNewHitBoxLeft(Point centerPosition, float radius, float angle, float atk);
	// �V���������蔻���ǉ�����֐��i�E�̉~�j
	// �����F
	// centerPosition ... �^�񒆂̍��W
	// width ... �q�b�g�{�b�N�X�̉����i����̓_����j
	// height ... �q�b�g�{�b�N�X�̏c���i����̓_����j
	// angle ... �q�b�g�Ώۂ̎l�p�̉�]�p�x
	// atk ... �_���[�W��
	static void MakeNewHitBoxRight(Point centerPosition, float radius, float angle, float atk);


	// �����蔻�茟��
	// �Ԃ�l�F�q�b�g���Ă����ꍇ -> ��_���[�W�ʁA�@�q�b�g���Ă��Ȃ��ꍇ -> 0
	// �����F
	// centerPosition ... ���؂�����W
	static float CheckHitBox(Point centerPosition);

private: // �����o�ϐ�

	// ���݂̓Y����
	static int num;

	struct HitBox {
		Point centerPosition;
		float width;
		float height;
		float angle;
		float atk;
	};
	// �����蔻��̃��X�g
	static HitBox hitBox[128];


	struct HitEllipse {
		Point centerPosition;
		float radius;
		float angle;
		float atk;
	};

	// ���̔��~�̓����蔻��
	static HitEllipse leftEllipse;
	// �E�̔��~�̓����蔻��
	static HitEllipse rightEllipse;
};