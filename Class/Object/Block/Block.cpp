#include "Class/Object/Block/Block.h"

// �R���X�g���N�^
Block::Block(Point _centerPosition, Point size) {

	centerPosition = _centerPosition;
	//width = size.x;
	//if (width < 64) {
		width = 64;
	//}
	//height = size.y;
	//if (height < 64) {
		height = 64;
	//}

	Initialize();
}
// �f�X�g���N�^
Block::~Block() {

}

// ������
void Block::SuccessorInitialize() {

	// ���x
	velocity = { 0,0 };
	// �����x
	acceleration = { 0,0 };

	// ��]�p�x�iDegree�j
	angle = rand() % 360;
	// ��]���x�iDegree�j
	angleVelocity = 0;

	//�󒆂ɂ��邩�ǂ���
	isFlying = true;
	isAlive = true;

	// �����蔻����O���ɓn��
	num = ObjectHitBox::AddHitBox(&centerPosition, &width, &height, &angle, &isAlive);
}
// �X�V
void Block::SuccessorUpdate() {
	
}
// �`��
void Block::Draw() {
	if (!isAlive) {
		return;
	}

	BaseDraw::DrawQuad(centerPosition, BaseTexture::kBlockTexture, { width,height }, 64.0f / width, angle, WHITE);
}

// �^�C�v���擾
ObjectType Block::GetType() {
	return typeBlock;
}
