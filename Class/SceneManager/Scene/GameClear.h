#pragma once
#include "MyBase/MyBase.h"
#include "Class/SceneManager/Scene/BaseScene.h"

class GameClear :
	public BaseScene{
public: // �����o�֐�

	// �R���X�g���N�^
	GameClear();
	// �f�X�g���N�^
	~GameClear();

	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private: // �����o�ϐ�
};