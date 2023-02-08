#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/Object.h"

#include "Class/Object/Block/Block.h"
#include "Class/Object/Block/FallBlock.h"
#include "Class/Object/Player/Player.h"
#include "Class/Object/Enemy/Balloon.h"
#include "Class/Object/Enemy/IronBalloon.h"
#include "Class/Object/Hook/Hook.h"
#include "Class/Object/Core/Core.h"

#include "Class/Wire/WireManager.h"

// �v���O�������̃I�u�W�F�N�g��S�ĊǗ�����N���X

class WireManager;

class ObjectManager {

public: // �����o�֐�

	// ������
	// �S�ẴI�u�W�F�N�g�̎��Ԃ��iObject�Łj������
	void Initialize();
	// �X�V
	// �S�ẴI�u�W�F�N�g���X�V�iUpdate���Ăяo���j
	void Update();
	// �`��
	// �S�ẴI�u�W�F�N�g��`��iDraw���Ăяo���j
	void Draw();


	// �V�����I�u�W�F�N�g�̃C���X�^���X�𐶐�����֐�����
	// ���̎��Ԃ�Object�̂��̂��Ⴂ�����D��ŏ㏑�����Ă���


	// Block
	void MakeNewObjectBlock(Point position, Point size);
	void MakeNewObjectFallBlock(Point position, bool isCanStub);

	// Player
	void MakeNewObjectPlayer(Point position, WireManager* wireManager);

	// Hook
	Object* MakeNewObjectHook(Point position, Point size);

	// Hook
	Object* MakeNewObjectCore(Point position, Point size);

	// Enemy
	void MakeNewObjectBalloon(Point position);
	void MakeNewObjectIronBalloon(Point position);

	// �S�Ă̎G���G����������
	void DeleteAllEnemy();

	// �I�u�W�F�N�g�̓����蔻����`�F�b�N����֐�
	// �Ԃ�l�F���̃I�u�W�F�N�g�̃|�C���^
	// �����F�`�F�b�N����Point
	//
	// �ЂƂ��q�b�g���Ă��Ȃ��ꍇ��NULL��Ԃ��i���̊֐����g���ꍇ�͕K��NULL�`�F�b�N�����邱�ƁI�j
	Object* CheckObjectHitBox(Point hitPosition);
	// �������󂯎���Ĕ���
	/// <summary>
	/// �I�u�W�F�N�g�̓����蔻����`�F�b�N����֐�
	/// </summary>
	/// <param name="hitPosition">�`�F�b�N����Point</param>
	/// <param name="hitVelocity">�����̃x�N�g��</param>
	/// <returns>���̃I�u�W�F�N�g�̃|�C���^</returns>
	Object* CheckObjectHitBox(Point hitPosition, Point hitVelocity);


	// �I�u�W�F�N�g�̓����蔻����`�F�b�N����֐�
	// �Ԃ�l�F���̃I�u�W�F�N�g�̃|�C���^
	// �����F�`�F�b�N����Point
	//
	// �ЂƂ��q�b�g���Ă��Ȃ��ꍇ��NULL��Ԃ��i���̊֐����g���ꍇ�͕K��NULL�`�F�b�N�����邱�ƁI�j
	Object* CheckObjectHitBox(Box hitPosition);

	/// <summary>
	/// �w�肵���I�u�W�F�N�g���擾����֐�
	/// </summary>
	/// <param name="objecttype">�I�u�W�F�N�g�^�C�v</param>
	/// <returns>Object</returns>
	Object* GetSelectObject(ObjectType objecttype);

	/// <summary>
	/// �S�I�u�W�F�N�g���Ƀu���b�N����������Ă��邩�ǂ������擾����֐�
	/// </summary>
	bool GetIsCreatedBlock();

	// �v���C���[�̒��S���W���󂯎��֐�
	Point GetPlayerPosition();
	// �v���C���[�ɔ͈͐�����ݒ肷��֐�
	// ������W�A�E�����W
	bool SetPlayerMoveLimit(Point, Point);
	// �v���C���[�͈̔͐����������֐�
	void DeletePlayerMoveLimit();

	// �v���C���[�̐����t���O���擾
	bool GetPlayerisAlive();


	// �R�A�Ƀu���b�N���q�b�g��������Ԃ��֐�
	bool isHitCore();

private: // �����o�萔

	const static int kMaxObjectSize = 256;

private: // �����o�ϐ�

	// �I�u�W�F�N�g�̃|�C���^�B
	Object* object[kMaxObjectSize];
};