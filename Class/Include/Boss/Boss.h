#pragma once
#include "MyBase/Include/MyBase.h"

/*********************************
	�{�X�N���X
*********************************/

class Boss {
public:

	//�R���X�g���N�^
	Boss();

	//�f�X�g���N�^
	~Boss();

	//������
	void Initialize();

	//�X�V����
	void Update(Point playerPosition);

	//�`�揈��
	void Draw();

private:
	/******** �s���֐� **********/
	//�s���Ȃ��i�s���Ԃ̑ҋ@���ԁj
	void None();
	//��]
	void Rotate();
	//�ːi
	void Rush();
	//�a��
	void Slash();
	//�ˌ�
	void Shot();
	//����
	void Fall();

	/******** �s���p�^�[��(Enum) **********/
	enum Attackpattern
	{
		NONE, //�s���Ȃ�
		ROTATE, //��]
		RUSH, //�ːi
		SLASH, //�a��
		SHOT, //�ˌ�
		FALL
	};
	int attackPattern = NONE;

};