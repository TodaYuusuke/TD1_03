#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/ObjectManager.h"
#include "Class/Wire/Wire.h"
#include "Class/Boss/Boss.h"

class ObjectManager;
class Player;
class Wire;

class WireManager {
public: // �����o�֐�

	// �R���X�g���N�^
	WireManager();
	// �f�X�g���N�^
	~WireManager();

	// ������
	void Initialize();
	// �X�V
	void Update(ObjectManager* objectManager);
	// �`��
	void Draw();

	// ���C���[�ˏo���ɌĂяo�����֐�
	// �Ԃ�l��true�̃p�^�[���F
	// �E����Ɏˏo�ł����ꍇ = 1
	// �Ԃ�l��false�̃p�^�[���F
	// �E���݃��C���[���ˏo���i�܂����e���Ă��Ȃ��j = -1
	// �E���łɃ��C���[�̒��e�_��2�_���܂��Ă��� = -2
	//
	// �����F
	// shotPosition ... ���C���[�ˏo�n�_
	// shotAngle ... ���ˊp�x�iDegree�j
	//
	// Wire�N���X��shot�̕Ԃ�l�Ő���Ɏˏo�ł������𔻒f���邱�ƁB
	int Shot(Point shotPosition, float shotAngle,Player* _player);

	// ���C���[�k�����ɌĂяo�����֐�
	// �Ԃ�l�F�Ȃ�
	// �����F�Ȃ�
	// ���e�_��Object�Ƀx�N�g���𑫂�
	//
	// �S�Ă�Wire��Attract()���Ăяo������
	void Attract();

private: // �����o�ϐ�

	// ���݂̃C���f�b�N�X
	int index;

	Wire* wires[BaseConst::kWireMaxAmount];

};