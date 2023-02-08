#pragma once
#include "MyBase/MyBase.h"

#include "Class/Object/ObjectManager.h"
#include "Class/Wire/WireManager.h"
#include "Class/Map/MapManager.h"

#include "Class/MiddleBoss/MiddleBoss.h"
#include "Class/Boss/Boss.h"

#include "Class/AttackHitBox/EnemyAttackHitBox.h"
#include "Class/AttackHitBox/ObjectHitBox.h"

#include "Class/PublicFlag/PublicFlag.h"

class BaseScene {
public: // �����o�֐�

	// ������
	virtual void Initialize() {
		nextScene = sceneNone;
	}
	// �X�V
	virtual void Update() {

	}
	// �`��
	virtual void Draw() {

	}

	// �V�[���ύX��������֐�
	// �Ԃ�l�F�V�[���ύX���Ȃ��ꍇ ... None
	// �@�@�@�@�@�@�@�@�@�@����ꍇ ... �ύX��̃V�[��
	virtual SceneState isGoNextScene() {
		return nextScene;
	}


protected: // �����o�ϐ�

	// ���̃V�[��
	SceneState nextScene;
};