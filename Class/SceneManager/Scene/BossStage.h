#pragma once
#include "MyBase/MyBase.h"
#include "Class/SceneManager/Scene/BaseScene.h"

#include "Class/Object/ObjectManager.h"
#include "Class/Wire/WireManager.h"
#include "Class/Map/MapManager.h"

#include "Class/Boss/Boss.h"

#include "Class/AttackHitBox/EnemyAttackHitBox.h"
#include "Class/AttackHitBox/ObjectHitBox.h"

#include "Class/PublicFlag/PublicFlag.h"


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

	ObjectManager objectManager;
	WireManager wireManager;
	Boss boss;
};