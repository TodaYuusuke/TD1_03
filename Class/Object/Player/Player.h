#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/Object.h"

#include "Class/Wire/WireManager.h"

#include "Class/AttackHitBox/EnemyAttackHitBox.h"

// �����܂ł��Ȃ��v���C���[
class WireManager;

enum PlayerState
{
	playerIdle,
	playerRun,
	playerJump,
	playerSky,
	playerLand,
	playerShot,
	playerAtrract
};

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

	// �����蔻����I�[�o�[���C�h

	// �I�u�W�F�N�g���̂̓����蔻����`�F�b�N����֐�
	void CheckFieldHitBox() override;

private: // �����o�ϐ�

	// ��ԃt���O

	// �Ə��̍��W
	Point reticlePosition;
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
	PlayerState state;



};