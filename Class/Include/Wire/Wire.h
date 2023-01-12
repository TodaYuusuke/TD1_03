#pragma once
#include "MyBase/Include/MyBase.h"
#include "Class/Include/Object/ObjectManager.h"

// ���C���[�̃N���X

class Wire {
public: // �����o�֐�

	// �R���X�g���N�^
	Wire();
	// �f�X�g���N�^
	~Wire();
	// �������i�ŏ��͑��݂��Ȃ����̂Ƃ��Ĉ����̂ŁA�ϐ��̓f�^�����Łj
	void Initialize();
	// �X�V
	void Update(ObjectManager objectManager);
	// �`��
	void Draw();


	// ���C���[�̓����蔻��`�F�b�N�p�֐�
	// �����F�Ȃ�
	// �Ԃ�l�F�q�b�g�����ꍇ ... true
	//
	// ����̓I�u�W�F�N�g�A�������͏�O�ɓ��������ꍇ�Ƀq�b�g����
	bool CheckHitBox(Point* _position, Object*& _object, ObjectManager objectManager);


	// ���C���[�ˏo���ɌĂяo�����֐�
	// �Ԃ�l��true�̃p�^�[���F
	// �E����Ɏˏo�ł����ꍇ
	// �Ԃ�l��false�̃p�^�[���F
	// �E���݃��C���[���ˏo���i�܂����e���Ă��Ȃ��j
	// �E���łɃ��C���[�̒��e�_��2�_���܂��Ă���
	//
	// �����F
	// shotPosition ... ���C���[�ˏo�n�_
	// shotAngle ... ���ˊp�x�iDegree�j
	//
	// ���̊֐����Ăяo���ꂽ��́AUpdate�ɂĒ��e����܂Œe�̉��Z���������邱�ƁB�i���C���[�̑��x��BaseConst::kWireSpeed�j
	bool Shot(Point shotPosition, float shotAngle, Player* _player);

	// ���C���[�k�����ɌĂяo�����֐�
	// �Ԃ�l�F�Ȃ�
	// �����F�Ȃ�
	// ���e�_��Object�Ƀx�N�g���𑫂�
	void Attract();


private: // �����o�ϐ�

	//���C���[�̏��
	enum WireState {
		// �ˏo���Ă��Ȃ�
		NoneShot,
		// �ˏo��
		DoneShot
	};
	WireState wireState;

	// 1�_�ڂ̍��W
	Point* firstPosition;
	// 2�_�ڂ̍��W
	Point* secondPosition;

	// 1�_�ڂ̒��n�_�ɂ������I�u�W�F�N�g
	Object* firstObject;
	// 2�_�ڂ̒��n�_�ɂ������I�u�W�F�N�g
	Object* secondObject;

	// �ˏo�p�x
	float ShotAngle;

};