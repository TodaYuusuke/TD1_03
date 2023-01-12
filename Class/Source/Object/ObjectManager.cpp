#include "Class/Include/Object/ObjectManager.h"

// �R���X�g���N�^
ObjectManager::ObjectManager() {

}
// �f�X�g���N�^
ObjectManager::~ObjectManager() {

}

// ������
// �S�ẴI�u�W�F�N�g�̎��Ԃ��iObject�Łj������
void ObjectManager::Initialize() {
	for (int i = 0; i < kMaxObjectSize; i++) {
		object[i] = new Object();
		object[i]->Initialize();
	}
}
// �X�V
// �S�ẴI�u�W�F�N�g���X�V�iUpdate���Ăяo���j
void ObjectManager::Update() {
	for (int i = 0; i < kMaxObjectSize; i++) {
		object[i]->Update();
	}
}
// �`��
// �S�ẴI�u�W�F�N�g��`��iDraw���Ăяo���j
void ObjectManager::Draw() {
	for (int i = 0; i < kMaxObjectSize; i++) {
		object[i]->Draw();
	}
}


// �V�����I�u�W�F�N�g�̃C���X�^���X�𐶐�����֐�����
// ���̎��Ԃ�Object�̂��̂��Ⴂ�����D��ŏ㏑�����Ă���


// Block
void ObjectManager::MakeNewObjectBlock(Point position, Point size) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == typeObject) {
			object[i] = new Block(position, size);
			object[i]->Initialize();
			break;
		}
	}
}

// Player
void ObjectManager::MakeNewObjectPlayer(Point position) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == typePlayer) {
			break;
		}
		if (object[i]->GetType() == typeObject) {
			object[i] = new Player(position);
			object[i]->Initialize();
			break;
		}
	}
}


// �I�u�W�F�N�g�̓����蔻����`�F�b�N����֐�
// �Ԃ�l�F���̃I�u�W�F�N�g�̃|�C���^
// �����F�`�F�b�N����Point
//
// �ЂƂ��q�b�g���Ă��Ȃ��ꍇ��NULL��Ԃ��i���̊֐����g���ꍇ�͕K��NULL�`�F�b�N�����邱�ƁI�j
Object* ObjectManager::CheckObjectHitBox(Point hitPosition) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == typeObject) {
			continue;
		}
		if (object[i]->CheckHitBox(hitPosition)) {
			return object[i];
		}
	}
	return NULL;
}


// �I�u�W�F�N�g�̓����蔻����`�F�b�N����֐�
// �Ԃ�l�F���̃I�u�W�F�N�g�̃|�C���^
// �����F�`�F�b�N����Point
//
// �ЂƂ��q�b�g���Ă��Ȃ��ꍇ��NULL��Ԃ��i���̊֐����g���ꍇ�͕K��NULL�`�F�b�N�����邱�ƁI�j
Object* ObjectManager::CheckObjectHitBox(Box hitPosition) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == typeObject) {
			continue;
		}
		if (object[i]->CheckHitBox(hitPosition)) {
			return object[i];
		}
	}
	return NULL;
}
