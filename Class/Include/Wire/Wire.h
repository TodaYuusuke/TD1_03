#include "MyBase/Include/MyBase.h"

// ���C���[�̃N���X

class Wire {
public: // �����o�֐�

	// �R���X�g���N�^
	Wire();
	// �f�X�g���N�^
	~Wire();

	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();

private: // �����o�ϐ�

	// 1�_�ڂ̍��W
	Point* firstPosition;
	// 2�_�ڂ̍��W
	Point* SecondPosition;



};