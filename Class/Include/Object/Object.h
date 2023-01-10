#include "MyBase/Include/MyBase.h"


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

protected: // �����o�ϐ�

	/* �萔�Ƃ��Ĉ����̂�Initialize�ȊO�̃v���O�������ŏ��������֎~�I�I */

	// �d�͉����x
	float kGravitationalAcceleration;

	/* �萔�����܂� */


	// ���S���W
	Point centerPosition;

	// �����蔻��̃T�C�Y�i����̓_����̒����j
	float width;
	float height;

	// ���x
	Point velocity;
	
	// �����x
	Point acceleration;

	// �󒆂ɂ��邩�ǂ���
	bool isFlying;

	// �e�N�X�`���n���h��
	int texture;

};