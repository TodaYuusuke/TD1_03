#pragma once
#include "MyBase/MyBase.h"

// �{�X�̐������铖���蔻����Ǘ�����N���X

class ObjectHitBox {
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
	static int AddHitBox(Point* _centerPosition, float* _width, float* _height, float* _angle);

	// �����蔻�茟��
	// �Ԃ�l�F�q�b�g���Ă����ꍇ -> true�A�@�q�b�g���Ă��Ȃ��ꍇ -> false
	// �����F
	// centerPosition ... ���؂�����W
	// num ... ���؂��Ȃ��Y����
	static bool CheckHitBox(Point _centerPosition, int noCheck);

private: // �����o�ϐ�

	// ���݂̓Y����
	static int num;
	// �����蔻��̃��X�g
	static Point* centerPosition[256];
	static float* width[256];
	static float* height[256];
	static float* angle[256];
	
};