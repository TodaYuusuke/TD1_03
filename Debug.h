#include "MyBase/MyBase.h"
#include "Class/Object/ObjectManager.h"
#include "Class/Wire/WireManager.h"

#include "Class/Map/MapManager.h"

#include "Class/Boss/Boss.h"

// �����ŊJ������ۂɁA�f�o�b�O�p�̏����͂�����ŗp�ӂ��邱�ƁB
// �J������class�̃C���X�^���X�Ȃǂ������ŌĂяo���A���������֐��������ŌĂяo���R�[�h���������ƁB

class Debug {

public: // �����o�֐�

	// �R���X�g���N�^
	Debug();
	// �f�X�g���N�^
	~Debug();

	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();


private: // �����o�ϐ�


	ObjectManager objectManager;
	WireManager wireManager;
	Boss boss;

};