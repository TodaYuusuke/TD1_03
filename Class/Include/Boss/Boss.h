#pragma once
#include "MyBase/Include/MyBase.h"

/*********************************************
 * �{�X�N���X
 *
 * �{�X�֘A�̍s�����ׂĂ��Ǘ�����N���X
 *********************************************/

class Boss {
public:

	// �R���X�g���N�^
	Boss();

	// �f�X�g���N�^
	~Boss();

	// ������
	void Initialize();

	// �X�V����
	void Update(Point playerPosition);

	// �`�揈��
	void Draw();

private:

	/*********************************
		�����o�֐�
	*********************************/

	/******** �ϊ��֐� **********/
	// �{�X���摜�̍��W�����߂�
	Point GetLCoverPosition(Point centerPosition);
	// �{�X�E�摜�̍��W�����߂�
	Point GetRCoverPosition(Point centerPosition);

	/******** �f�o�b�O�֐� **********/
	void Debug();

	/******** �U���s���֐� **********/
	// �s���Ȃ��i�s���Ԃ̑ҋ@���ԁj
	void None(int waitTime);
	//��]
	void Rotate();
	// �ːi
	void Rush();
	// �a��
	void Slash();
	// �ˌ�
	void Shot();
	// ����
	void Fall();

	/******** �X�^���֐� **********/
	void Stun();

	/******** �_���[�W **********/
	void Damage();

	/*********************************
		�����o�萔
	*********************************/

	/******** ���C���[�������邱�Ƃ̂ł���ꏊ�̍ő吔 **********/
	const static int kmaxWireHang = 2;

	/******** �\���ł���e�̍ő吔 **********/
	const static int kmaxBullet = 50;

	/*********************************
		�����o�ϐ�
	*********************************/

	/******** �f�o�b�O�ɗp����ϐ� **********/
	//���݃f�o�b�O��Ԃ�
	bool inDebug = false;

	/******** �s���p�^�[��(Enum) **********/
	enum Attackpattern
	{
		NONE, // �s���Ȃ�
		ROTATE, // ��]
		RUSH, // �ːi
		SLASH, // �a��
		SHOT, // �ˌ�
		FALL
	};
	// �U���p�^�[�����i�[����int�^�ϐ�
	int attackPattern = NONE;

	/******** �s�����Ԓn�_�iEnum�j **********/
	// �U����X�^�����̒��Ԓn�_���B�̍ۂɐ؂�ւ�
	enum ActionWayPoint 
	{
		WAYPOINT1, // �s�����Ԓn�_�`
		WAYPOINT2,
		WAYPOINT3,
		WAYPOINT4,
		WAYPOINT5
	};

	/******** ���W�֘A **********/
	/// �{�X�֘A
	// ���S���W
	Point centerPosition;
	
	// �{�X�����E�ɂǂꂾ���J����
	float offset;
	// �{�X�̉�]�p�idegree���j
	int degree;

	// �j�̒��S���W�i�ړ�������\�������邽�߁j
	Point coreCenterPosition;
	// �j�̉�]�p�idegree���j
	int coreDegree;

	// ���C���[�����������钆�S���W
	Point wireHangPosition[kmaxWireHang];

	/******** �T�C�Y�֘A **********/
	/// �{�X�֘A

	// �e�N�X�`���T�C�Y
	Point textureSize;
	// �j�̃e�N�X�`���T�C�Y
	Point kernelTextureSize;

	// �T�C�Y
	Point size;
	// �j�̃T�C�Y
	Point coreSize;
	
	/******** �s���֘A **********/
	/// �U���֘A
	// �U������
	bool inAction;
	// �U�����I�����Ă��邩
	bool endAction;

	/// �X�^���֘A
	// �X�^������
	bool inStun;
	// �X�^�����鎞��
	int stunTime;

	/// �_���[�W�֘A
	// �_���[�W���󂯂Ă���̂�
	bool inDamage;

	// �j���������Ă��邩
	bool coreSeparated;

	/******** �C�[�W���O�֘A **********/
	// �C�[�W���O�pt
	float t = 0.0f;

};