#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/ObjectManager.h"

#include "Class/Map/MapManager.h"

// ���C���[�̃N���X

class ObjectManager;
class Player;

class Wire {
public: // �����o�֐�

	// �R���X�g���N�^
	Wire();
	// �f�X�g���N�^
	~Wire();
	// �������i�ŏ��͑��݂��Ȃ����̂Ƃ��Ĉ����̂ŁA�ϐ��̓f�^�����Łj
	void Initialize();
	// �X�V
	void Update(ObjectManager* objectManager);
	// �`��
	void Draw();

	// ���C���[�̐����t���O��Ԃ�
	bool GetisAlive();

	// ���C���[�̓����蔻��`�F�b�N�p�֐�
	// �����F�Ȃ�
	// �Ԃ�l�F�q�b�g�����ꍇ ... true
	//
	// ����̓I�u�W�F�N�g�A�������͏�O�ɓ��������ꍇ�Ƀq�b�g����
	bool CheckHitBox(Point _position, int i, ObjectManager* objectManager);


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

	// 0 ... �P���ځiFirst�j
	// 1 ... �Q���ځiSecond�j

	// �O�t���[���̍��W
	Point prePosition[2];
	// ���W
	Point position[2];
	// ���n�_�̃I�u�W�F�N�g
	Object* object[2];
	// ���n�_�̃I�u�W�F�N�g�̃^�C�v
	ObjectType type[2];
	// ���C���[�̏��
	bool isShot[2];

	// �ˏo�p�x�idegree�j
	float shotAngle;

	// ���C���[�̐����t���O
	bool isAlive;
};