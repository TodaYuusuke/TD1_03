#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/Object.h"

#include "Class/Wire/WireManager.h"

#include "Class/AttackHitBox/EnemyAttackHitBox.h"

// �����܂ł��Ȃ��v���C���[
class WireManager;

class Player :
	public Object {
public: // �����o�֐�

	// �R���X�g���N�^
	Player(Point centerPosition,WireManager* _wireManager);
	// �f�X�g���N�^
	~Player();

	// ������
	void SuccessorInitialize() override;
	// �X�V
	void SuccessorUpdate() override;
	// �`��
	void Draw() override;

	// �^�C�v�擾
	ObjectType GetType() override;


private: // �֐�


	// �ǂ����Update()�Ŗ��t���[���Ăяo������

	// �ړ��֘A
	void Move();
	// �W�����v
	void Jump();
	// ���C���[�֘A
	void ShotWire();

	// �����蔻����I�[�o�[���C�h
	
	// �I�u�W�F�N�g���̂̓����蔻����`�F�b�N����֐�
	void CheckFieldHitBox() override;

private: // �����o�ϐ�

	// ��ԃt���O

	// �Ə��̍��W
	Point reticlePosition;


	// ���C���[�Ǘ��N���X
	WireManager* wireManager;

	// �q�b�g��̖��G����
	int invincibleFrame;
	// ���݉E�������Ă��邩�ǂ���
	bool isRight;

	// �J�������ړ������邽�߂� t
	float screenT;

	//////////////
	/// HP�֘A ///
	//////////////
	
	// ���킸������
	int HP;
	// HP ��\�����邩�ǂ���
	bool isDrawHP;
	// HP ��\������t���[����
	int drawHPFrame;



	//////////////
	///�����܂�///
	//////////////




};