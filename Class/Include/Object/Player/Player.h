#include "MyBase/Include/MyBase.h"
#include "Class/Include/Object/Object.h"

// �����܂ł��Ȃ��v���C���[


// ���}�g��


class Player :
	public Object {
public: // �����o�֐�

	// �R���X�g���N�^
	Player(Point centerPosition);
	// �f�X�g���N�^
	~Player();

	// ������
	void SuccessorInitialize() override;
	// �X�V
	void SuccessorUpdate() override;
	// �`��
	void Draw() override;

};