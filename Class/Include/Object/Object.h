#pragma once
#include "MyBase/Include/MyBase.h"

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
	

	// �I�u�W�F�N�g�ɑ��x�x�N�g���𑫂��֐�
	// �Ԃ�l�F�Ȃ�
	// �����F�������x
	void AddVelocity(Point _addVelocity);

	// �I�u�W�F�N�g�ɉ�]���x�𑫂��֐�
	// �Ԃ�l�F�Ȃ�
	// �����F�������x
	void AddVelocity(float _addVelocity);

	// �����蔻����`�F�b�N����֐�
	// �Ԃ�l�F�q�b�g���Ă����ꍇ ... true
	// �����F�`�F�b�N����Point
	bool CheckHitBox(Point hitPosition);

	// �����蔻����`�F�b�N����֐�
	// �Ԃ�l�F�q�b�g���Ă����ꍇ ... true
	// �����F�`�F�b�N����Box
	bool CheckHitBox(Box hitPosition);

	/// <summary>
	/// �t�B�[���h�O�ւ̈ړ����`�F�b�N����֐�
	/// </summary>
	/// <returns>�t�B�[���h�O�ɏo���ꍇ ... true</returns>
	bool CheckFieldHitBox();

	/// <summary>
	/// �^�C�v���擾����֐�
	/// </summary>
	/// <returns>�I�u�W�F�N�g�̃^�C�v</returns>
	virtual ObjectType GetType();

	/// <summary>
	/// ���W���擾����֐�
	/// </summary>
	/// <returns>centerPosition</returns>
	Point GetCenterPosition();

	/// <summary>
	/// ���x���擾����֐�
	/// </summary>
	/// <returns>velocity</returns>
	Point GetVelocity();

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


};