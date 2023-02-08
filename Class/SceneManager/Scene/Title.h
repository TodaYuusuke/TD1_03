#pragma once
#include "MyBase/MyBase.h"
#include "Class/SceneManager/Scene/BaseScene.h"

class Title :
	public BaseScene {
public: // �����o�֐�

	// �R���X�g���N�^
	Title();
	// �f�X�g���N�^
	~Title();

	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private: // �����o�ϐ�

	// �R���g���[�����܂߂����W
	Point reticlePosition;
	Point preMousePosition;
	// �X�^�[�g��I�����Ă��邩
	bool isToPlay;
	bool isToEnd;
	// �I��������
	bool isSelected;

	// �t�F�[�h�A�E�g�p
	int feedOutFlame;
	int feedInFlame;

	const int kFeedInMax = 60;
	const int kFeedOutMax = 60;

};