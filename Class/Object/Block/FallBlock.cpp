#include "Class/Object/Block/FallBlock.h"

// �R���X�g���N�^
FallBlock::FallBlock(Point _centerPosition, bool isCanStub) {

	centerPosition = _centerPosition;
	//width = size.x;
	//if (width < 64) {
	width = 64;
	//}
	//height = size.y;
	//if (height < 64) {
	height = 64;
	//}
	this->isCanStub = isCanStub;

	Initialize();
}
// �f�X�g���N�^
FallBlock::~FallBlock() {

}

// ������
void FallBlock::SuccessorInitialize() {

	// ���x
	velocity = { 0,-22 };
	// �����x
	acceleration = { 0,0 };

	// ��]�p�x�iDegree�j
	angle = rand() % 360;
	// ��]���x�iDegree�j
	angleVelocity = 0;

	//�󒆂ɂ��邩�ǂ���
	isFlying = true;
	isAlive = true;

	// ���Ńt���O
	vanishFlame = BaseConst::kBlockVanishFlame;

	// �����蔻����O���ɓn��
	num = ObjectHitBox::AddHitBox(&centerPosition, &width, &height, &angle, &isAlive);
}
// �X�V
void FallBlock::SuccessorUpdate() {
	if (!isAlive) {
		return;
	}

	// ���C���[���h�������珉����
	if (isStub) {
		vanishFlame = BaseConst::kBlockVanishFlame;
		// ���C���[���h����Ȃ��ꍇ�̏���
		if (!isCanStub) {
			isStub = false;
		}
	}
	// �h�����ĂȂ������猸�炷
	else {
		vanishFlame--;
	}

	if (vanishFlame < 0) {
		isAlive = false;
	}

}
// �`��
void FallBlock::Draw() {
	if (!isAlive) {
		return;
	}
	// �O���̈�ȉ��Ȃ� 10 �t���[�����ɓ_��
	if (vanishFlame < BaseConst::kBlockBeVanish && vanishFlame % 10 == 0) {
		BaseDraw::DrawQuad(centerPosition, BaseTexture::kBlockTexture, { width,height }, 64.0f / width, angle, 0x777777FF);
	}
	else {
		BaseDraw::DrawQuad(centerPosition, BaseTexture::kBlockTexture, { width,height }, 64.0f / width, angle, WHITE);
	}
}

// �^�C�v���擾
ObjectType FallBlock::GetType() {
	return typeFallBlock;
}
