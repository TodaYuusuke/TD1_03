#include "Class/Include/Object/Block/Block.h"

// �R���X�g���N�^
Block::Block(Point _centerPosition, Point size) {

	centerPosition = _centerPosition;
	width = size.x;
	height = size.y;

}
// �f�X�g���N�^
Block::~Block() {

}

// ������
void Block::SuccessorInitialize() {

	velocity = { 0,0 };
	acceleration = { 0,0 };

	isFlying = true;

	texture = BaseTexture::kDebugTexture;

}
// �X�V
void Block::SuccessorUpdate() {

}
// �`��
void Block::Draw() {
	BaseDraw::DrawQuad(centerPosition, texture, { 100,100 }, 1.0f, 0.0f, WHITE);
}