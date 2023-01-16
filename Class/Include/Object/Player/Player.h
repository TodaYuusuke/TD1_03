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
	// �W�����v
	void Jump();
	// ���C���[�֘A
	void ShotWire();


private: // �����o�ϐ�

	// ��ԃt���O

	// �Ə��̍��W
	Point reticlePosition;


	// ���C���[�Ǘ��N���X
	WireManager* wireManager;

};