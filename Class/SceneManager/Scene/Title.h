#pragma once
#include "MyBase/MyBase.h"
#include "Class/SceneManager/Scene/BaseScene.h"

class Title :
	public BaseScene{
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
};