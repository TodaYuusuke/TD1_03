#include "MyBase/Include/MyBase.h"
#include "Class/Include/Object/ObjectManager.h"
#include "Class/Include/Wire/WireManager.h"

#include "Class/Include/Map/MapManager.h"

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

};