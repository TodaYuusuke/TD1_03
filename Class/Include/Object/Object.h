#pragma once
#include "MyBase/Include/MyBase.h"

#include "Class/Include/Map/MapManager.h"

enum ObjectType {
	// �I�u�W�F�N�g
	typeObject,
	// �u���b�N
	typeBlock,
	// �v���C���[
	typePlayer
};


// �S�ẴI�u�W�F�N�g�ɋ��ʂ��鏈������������

/*

�E�d�͂ɂ�����

*/



class Object {
public: // �����o�֐�

	// �R���X�g���N�^
	//Object();
	// �f�X�g���N�^
	//~Object();

	// ������ ... Objdct�ɒ�`����Ă�萔��������
	// ���R�[�h���ɕK��SuccessorInitialize���Ăяo������
	virtual void Initialize();
	// �p����̏����� ... �p�����ƌp����ɒ�`����Ă�ϐ���������
	virtual void SuccessorInitialize();
	
	// �X�V ... �S�I�u�W�F�N�g���ʂ̏���
	// ���R�[�h���ɕK��SuccessorUpdate���Ăяo������
	virtual void Update();
	// �p����̍X�V ... �p������L�̏���
	virtual void SuccessorUpdate();
	
	// �`��
	virtual void Draw();
	

	// �����o�ϐ��ɍ�p����֐�

	// �I�u�W�F�N�g�̒��S���W���󂯎��֐�
	// �Ԃ�l�F���S���W
	// �����F�Ȃ�
	Point GetCenterPosition();

	// �I�u�W�F�N�g�̑��x���󂯎��֐�
	// �Ԃ�l�F���x�̃x�N�g��
	// �����F�Ȃ�
	Point GetVelocity();

	// �I�u�W�F�N�g���󒆂��ǂ������󂯎��֐�
	// �Ԃ�l�F�󒆂Ȃ��true
	// �����F�Ȃ�
	bool GetisFlying();

	// �I�u�W�F�N�g�ɑ��x�x�N�g���𑫂��֐�
	// �Ԃ�l�F�Ȃ�
	// �����F�������x�̃x�N�g��
	void AddVelocity(Point _addVelocity);

	// �I�u�W�F�N�g�ɉ�]���x�𑫂��֐�
	// �Ԃ�l�F�Ȃ�
	// �����F�������x
	void AddVelocity(float _addVelocity);

	
	// �����蔻��֘A

	// �I�u�W�F�N�g�ɑ΂��铖���蔻����`�F�b�N����֐�
	// �Ԃ�l�F�q�b�g���Ă����ꍇ ... true
	// �����F�`�F�b�N����Point
	bool CheckHitBox(Point hitPosition);

	// �����蔻����`�F�b�N����֐�
	// ���@����angle���l�����������ɂȂ��Ă��Ȃ��̂ŁA�g�p�֎~�@��
	// �Ԃ�l�F�q�b�g���Ă����ꍇ ... true
	// �����F�`�F�b�N����Box
	bool CheckHitBox(Box hitPosition);


	// ���̑�

	// �^�C�v���擾����֐�
	// �Ԃ�l�F���g��ObjectType
	// �����F�Ȃ�
	virtual ObjectType GetType();

protected: // �֐�

	// �I�u�W�F�N�g���̂̓����蔻����`�F�b�N����֐�
	virtual void CheckFieldHitBox();
	// �㉺���E�̓����蔻��̊֐�
	virtual void CheckHitBoxRhombus(Point checkQuadPoint[], Point checkRhombusPoint[]);

	// �ł��߂��l���i�[�����z��̓Y���������߂�
	int GetNearestValue(int v) {
		// �ϐ��̐錾
		//v = BaseMath::Clamp(v, 0, 360);
		if (v < 45) {
			return 0;
		}
		else if (v < 90 + 45) {
			return 90;
		}
		else if (v < 180 + 45) {
			return 180;
		}
		else if (v < 270 + 45) {
			return 270;
		}
		else {
			return 0;
		}
	}

	/// <summary>
	/// ��]�p�x���擾����֐�
	/// </summary>
	/// <returns>angle</returns>
	float GetAngle();

	/// <summary>
	/// ��`�̂S�_���擾����֐�
	/// </summary>
	/// <returns>Quad</returns>
	Quad GetQuad();

protected: // �����o�ϐ�

	// ���S���W
	Point centerPosition;
	// ���x
	Point velocity;
	// �����x
	Point acceleration;

	// ��]�p�x�iDegree�j
	float angle;
	// ��]���x�iDegree�j
	float angleVelocity;

	// �����蔻��̃T�C�Y�i����̓_����̒����j
	float width;
	float height;

	//�󒆂ɂ��邩�ǂ���
	bool isFlying;

	// 0 ... ��
	// 1 ... ��
	// 2 ... ��
	// 3 ... �E
	// ��4�_��p��
	Point checkRhombusPoint[4];

	// 0 ... ����
	// 1 ... �E��
	// 2 ... ����
	// 3 ... �E��
	// ��4�_��p��
	Point checkQuadPoint[4];
};