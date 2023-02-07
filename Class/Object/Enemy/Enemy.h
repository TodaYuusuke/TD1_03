#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/Object.h"



class Enemy :public Object
{
public:
	// �R���X�g���N�^
	Enemy(Point centerPosition, Point size, Object* _object);
	// �f�X�g���N�^
	~Enemy();

	// ������
	void SuccessorInitialize() override;
	// �X�V
	void SuccessorUpdate() override;
	// �`��
	void Draw() override;
	// �^�C�v�擾
	ObjectType GetType() override;

private:

	// -1 : ��
	//	1 : �E
	//  0 : ��~
	int direct;


	// �v���C���[�̍��W���Q��
	Object* object;

};
