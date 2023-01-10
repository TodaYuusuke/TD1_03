#include "MyBase/Include/MyBase.h"
#include "Class/Include/Object/Object.h"

#include "Class/Include/Object/Block/Block.h"
#include "Class/Include/Object/Player/Player.h"



// �v���O�������̃I�u�W�F�N�g��S�ĊǗ�����N���X


class ObjectManager {

public: // �����o�֐�

	// �R���X�g���N�^
	ObjectManager();
	// �f�X�g���N�^
	~ObjectManager();

	// ������
	// �S�ẴI�u�W�F�N�g�̎��Ԃ��iObject�Łj������
	void Initialize();
	// �X�V
	// �S�ẴI�u�W�F�N�g���X�V�iUpdate���Ăяo���j
	void Update();
	// �`��
	// �S�ẴI�u�W�F�N�g��`��iDraw���Ăяo���j
	void Draw();


	// �V�����I�u�W�F�N�g�̃C���X�^���X�𐶐�����֐�����
	// ���̎��Ԃ�Object�̂��̂��Ⴂ�����D��ŏ㏑�����Ă���
	

	// Block
	void MakeNewObjectBlock(Point position, Point size);

	// Player
	void MakeNewObjectPlayer(Point position);



private: // �����o�萔

	const static int kMaxObjectSize = 256;

private: // �����o�ϐ�

	// �I�u�W�F�N�g�̃|�C���^�B
	Object* object[kMaxObjectSize];

};