#pragma once
#include "MyBase/MyBase.h"
#include "Class/SceneManager/Scene/BaseScene.h"

class BossStage :
	public BaseScene{
public: // �����o�֐�

	// �R���X�g���N�^
	BossStage();
	// �f�X�g���N�^
	~BossStage();

	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private: // �����o�ϐ�
};