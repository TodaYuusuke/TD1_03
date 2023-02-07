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
	Player(Point centerPosition, WireManager* _wireManager);
	// �f�X�g���N�^
	~Player();

	// ������
	void SuccessorInitialize() override;
	// �X�V
	void Update() override;
	// �X�V
	void SuccessorUpdate() override;
	// �`��
	void Draw() override;

	// �^�C�v�擾
	ObjectType GetType() override;

	// �ړ�����
	bool GetIsLimitMove() { return isLimitMove; };
	// �ړ���������
	Point GetLimitLeftTop() { return limitLeftTop; };
	// �ړ������E��
	Point GetLimitRightBottom() { return limitRightBottom; };


	// �ړ�����
	void SetIsLimitMove(bool a) { isLimitMove = a; };
	// �ړ���������
	void SetLimitLeftTop(Point p) { limitLeftTop = p; };
	// �ړ������E��
	void SetLimitRightBottom(Point p) { limitRightBottom = p; };

private: // �֐�


	// �ǂ����Update()�Ŗ��t���[���Ăяo������

	// �ړ��֘A
	void Move();
	// �Ə��ړ�
	void ReticleMove();
	// �W�����v
	void Jump();
	// ���C���[�֘A
	void ShotWire();

	// �ړ������֐�
	void LimitMovement();

	// ���X�|�[���֐�
	void Respawn();

	// �A�j���[�V����
	void Animation();


	// �����蔻����I�[�o�[���C�h

	// �I�u�W�F�N�g���̂̓����蔻����`�F�b�N����֐�
	void CheckFieldHitBox() override;

private: // �����o�ϐ�

	// ��ԃt���O

	// �Ə��̍��W
	Point reticlePosition;
	// �O�̏Ə��̍��W
	Point preReticlePosition;
	// �O�̃t���[���̃}�E�X���W
	Point preMousePosition;


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

	// �v���C���[�̈ړ�����
	bool isLimitMove;

	// �������鍶����W
	Point limitLeftTop;
	// ��������E�����W
	Point limitRightBottom;

	// �A�j���[�V����
	// ���̏��
	int state;
	// �O�̏��
	int preState;
	// ��Ԃ��ς���Ă���̏��
	int buffState;

	// ��Ԃ��ς���Ă���̃t���[����
	int stateChengeFlame;

	// �A�j���[�V�����p�t���[���J�E���g
	int animationFlameCount;

	// ���̃A�j���[�V�����t���[��
	int animationFlame;


	// ���X�|�[���n�_
	Point resqawnPosition;

	// ���X�|�[���p�O�t���[�����W
	Point preCenterPosition;

	// isFlying ��false�ɂȂ����u�Ԃ̊��m
	bool preIsFlying;

	// ���X�|�[�����邩
	bool isRespawn;

};