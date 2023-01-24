#include "MyBase/Effect/BaseEffectManager.h"


// ������
void BaseEffectManager::Initialize() {
	for (int i = 0; i < effectArraySize; i++) {
		effects[i] = new BaseEffect();
		effects[i]->BaseInitialize();
	}

	nextIndex = -1;
}
// �X�V
void BaseEffectManager::Update() {
	for (int i = 0; i < effectArraySize; i++) {
		effects[i]->BaseUpdate();
	}
}
// �`��
void BaseEffectManager::Draw() {
	for (int i = 0; i < effectArraySize; i++) {
		effects[i]->BaseDraw();
	}
}



// �V�K�G�t�F�N�g�o�^�֐�
// �Ԃ�l�F�G�t�F�N�g���Z�b�g���ꂽ�ԍ�
// �����F
// position ... ���S�̃��[���h���W
// angle ... ��]�p�x�iDegree�j
// effectType ... �G�t�F�N�g�̎��
int BaseEffectManager::MakeNewEffect(Point position, EffectType effectType) {

	// �ǉ�����܂Ń��[�v
	while (true) {

		nextIndex++;
		if (nextIndex >= effectArraySize) {
			nextIndex = 0;
		}

		if (effects[nextIndex]->isEndEffect()) {
			switch (effectType)
			{
				case EffectType::NoEffect:
				default:
					break;
			}
			break;
		}

	}

	return nextIndex;
}


// �G�t�F�N�g���I��������֐�
// �Ԃ�l�F�Ȃ�
// �����F
// effectNum ... �G�t�F�N�g�ԍ�
void BaseEffectManager::EndEffect(int effectNum) {
	return effects[effectNum]->EndEffect();
}


// �G�t�F�N�g���I���������𒲂ׂ�֐�
// �Ԃ�l�F�G�t�F�N�g���I���ς� ... true �A �����łȂ��ꍇ ... false
// �����F
// effectNum ... �G�t�F�N�g�ԍ�
bool BaseEffectManager::isEndEffect(int effectNum) {
	return effects[effectNum]->isEndEffect();
}


//////////////////////////////////
/* - static�����o�ϐ��̎��Ԃ�錾 - */
//////////////////////////////////

// �G�t�F�N�g�̔z��
BaseEffect* BaseEffectManager::effects[effectArraySize];
// ���ɒǉ�����G�t�F�N�g�̓Y��
int BaseEffectManager::nextIndex;