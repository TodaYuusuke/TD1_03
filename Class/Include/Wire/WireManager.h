#pragma once
#include "MyBase/Include/MyBase.h"
#include "Class/Include/Object/ObjectManager.h"
#include "Wire.h"

class ObjectManager;

class WireManager {
public: // �����o�֐�

	// �R���X�g���N�^
	WireManager();
	// �f�X�g���N�^
	~WireManager();

	// ������
	void Initialize();
	// �X�V
	void Update(ObjectManager objectManager);
	// �`��
	void Draw();

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
	// Wire�N���X��shot�̕Ԃ�l�Ő���Ɏˏo�ł������𔻒f���邱�ƁB
	bool Shot(Point shotPosition, float shotAngle);

	// ���C���[�k�����ɌĂяo�����֐�
	// �Ԃ�l�F�Ȃ�
	// �����F�Ȃ�
	// ���e�_��Object�Ƀx�N�g���𑫂�
	//
	// �S�Ă�Wire��Attract()���Ăяo������
	void Attract();

private: // �����o�ϐ�

	Wire wires[3];

};