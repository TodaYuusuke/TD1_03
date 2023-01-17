#include "Class/Include/Boss/Boss.h"

/*********************************
	�{�X�N���X
*********************************/

//�R���X�g���N�^
Boss::Boss() {
	Boss::Initialize();
}

//�f�X�g���N�^
Boss::~Boss() {

}

//����������
void Boss::Initialize() {
	//�{�X�̈ʒu����ʒ����Ɏ����Ă���
	this->centerPosition = { (float)(BaseConst::kWindowWidth / 2),(float)(BaseConst::kWindowHeight / 2) };
	//�{�X�̉摜�T�C�Y��ݒ�
	this->textureSize = { 225.0f, 450.0f };

	//�j�̈ʒu��ݒ�
	kernelCenterPosition = centerPosition;
	//�j�̉摜�T�C�Y��ݒ�
	kernelTextureSize = { 256.0f, 256.0f };
}

//�X�V����
void Boss::Update(Point playerPosition) {

}

//�`�揈��
void Boss::Draw() {

	//�{�X�j�摜
	BaseDraw::DrawQuad(
		kernelCenterPosition,
		BaseTexture::kBossKernel,
		kernelTextureSize,
		1.0f,
		0.0f,
		0xFFFFFFFF
	);

	//�{�X�����摜
	BaseDraw::DrawQuad(
		centerPosition,
		BaseTexture::kBossLCover,
		textureSize,
		1.0f,
		0.0f,
		0xFFFFFFFF
	);

	//�{�X�E���摜
	BaseDraw::DrawQuad(
		centerPosition,
		BaseTexture::kBossRCover,
		textureSize,
		1.0f,
		0.0f,
		0xFFFFFFFF
	);
}