#pragma once
#include "MyBase/Include/MyBase.h"
#include "Class/Include/Object/Object.h"

#include "Class/Include/Wire/WireManager.h"


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
	// ���C���[���ˏo���铮��
	void ShotWire();

private: // �����o�ϐ�


	// �}�E�X���W
	Point ReticlePosition;

	WireManager* wireManager;

};