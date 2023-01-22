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

	// ����摜�̑��΍��W�����߂�
	Point GetWeaponPosition(Point centerPosition);

	// ���˒n�_�̑��΍��W�����߂�
	Point GetShotPosition(Point centerPosition);

	/******** �������֐� **********/
	// �I���������֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// cenerPosition ... ���W�����������邩
	// degree ... �p�x�����������邩
	// offset ... �I�t�Z�b�g�����������邩
	// t ... t�����������邩
	// weapon ... ����֌W�̕ϐ������������邩
	// ������True�ɂ������̂�������������֐�
	void SelectionInitialize(bool centerPosition, bool degree, bool offset, bool t, bool weapon);

	/******** �f�o�b�O�֐� **********/
	void Debug();

	/******** ���̑��s���֐� **********/

	//�C�[�Y�A�E�g�iInt�^�j
	 int IntEaseOut(float t, long int b, long int c) {
		float easeT = 1.0f - powf(1.0f - t, 3.0f);
		return (1.0f - easeT) * b + easeT * c;
	}

	// �V�F�C�N�֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// shakeStrength ... �V�F�C�N����ۂ̋���
	// �{�X���V�F�C�N������֐�
	void Shake(int shakeStrength);

	// �V�F�C�N�C�[�Y�A�E�g�֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// shakeStrength ... �V�F�C�N����ۂ̋���
	// �{�X���V�F�C�N�̋������������キ���Ȃ��瓮�����֐�
	void ShakeEaseOut(int shakeStrength, float shakeTime);

	// �V�F�C�N�C�[�Y�C���A�E�g�֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// shakeStrength ... �V�F�C�N����ۂ̋���
	// �{�X���V�F�C�N�̋������������キ���Ȃ��瓮�����֐�
	void ShakeEaseInOut(int shakeStrength, float shakeTime);

	/******** �U���s���֐� **********/
	// �s���Ȃ��֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// waitTime ... �ҋ@����b��
	// �s���̍��Ԃɋ��ފ֐��B
	void None(float waitFrame);

	// ��]�֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// endDegree ... �I�����̊p�x
	// rotateTime ... ��]���鎞�ԁB����͕b��
	// �{�X����]������֐�
	void Rotate(float endDegree, float RotateTime);

	// �ːi�֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// playerPosition ... �v���C���[�̍��W
	// readyTime ... �ːi�̏����ɂ�����b��
	// rushTime ... �ːi�ɂ�����b��
	// backTime ... �߂鎞�ɂ�����b��
	// �{�X���v���C���[�̌����ɓːi������֐�
	void Rush(Point playerPosition, float readyTime , float rushTime, float backTime);

	// �a���֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// playerPosition ... �v���C���[�̍��W
	// readyTime ... �{�X���J���܂łɂ�����b��
	// deployTime ... �u���[�h�̓W�J�ɂ�����b��
	// preparationTime�@... �U���܂ł̑ҋ@����
	// rushTime ... �ːi�ɂ�����b��
	// backTime ... �߂鎞�ɂ�����b��
	// �{�X���a�����s���֐�
	void Slash(Point playerPosition, float readyTime, float deployTime, float preparationTime, float slashTime, float backTime);
	
	// �ˌ��֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// playerPosition ... �v���C���[�̍��W
	// readyTime ... �{�X���J���܂łɂ�����b��
	// deployTime ... �e�̓W�J�ɂ�����b��
	// preparationTime�@... �U���܂ł̑ҋ@����
	// shotTime ... �ˌ��b��
	// backTime ... �߂鎞�ɂ�����b��
	// fireRate ... ���b�����Ɏˌ����邩
	// �{�X���ˌ����s���֐�
	void Shot(Point playerPosition, float readyTime, float deployTime, float preparationTime, float shotTime, float backTime, float fireRate);

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
		�����o�ϐ��@	
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
		WAYPOINT0, // ������
		WAYPOINT1, // �s�����Ԓn�_�`
		WAYPOINT2,
		WAYPOINT3,
		WAYPOINT4,
		WAYPOINT5
	};
	//�s�����ǂ��܂Ői��ł��邩���i�[����ϐ�
	int actionWayPoint = WAYPOINT0;

	/******** �s������(Enum) **********/
	// �s���������_���ɕ��򂳂���B�����l��Pattern1
	enum ActionBranch {
		Pattern1, //�s������ 1~
		Pattern2,
		Pattern3
	};
	// �ǂ̍s���ɕ��򂳂��邩���i�[����ϐ�
	int actionBranch = Pattern1;

	/******** ���W�֘A **********/
	/// �{�X�֘A
	// ���S���W
	Point centerPosition;
	// �V�F�C�N����Ƃ��̍��W�̕ω���
	Point shakeVariation;
	// �V�F�C�N����͈�
	int shakeRange;
	
	// �{�X�����E�ɂǂꂾ���J����
	float offset;
	// �{�X�̉�]�p�idegree���j
	int degree;

	// �j�̒��S���W�i�ړ�������\�������邽�߁j
	Point coreCenterPosition;
	// �j�̉�]�p�idegree���j
	int coreDegree;

	// �e�̔��˒n�_
	Point shotPoint;

	// ���C���[�����������钆�S���W
	Point wireHangPosition[kmaxWireHang];

	// �s���O���W
	Point prevCenterPosition;
	// �s������W
	Point nextCenterPosition;

	// �s���O�p�x
	int prevDegree;
	// �s����p�x
	int nextDegree;

	// �s���O�I�t�Z�b�g
	int prevOffset;
	// �s����I�t�Z�b�g
	int nextOffset;

	// �Q�Ƃ���v���C���[���W
	Point prePlayerPosition;

	// �v���C���[�ւ̕���
	float playerDirection;

	/// �e�֘A
	// �e�̒��S���W
	Point bulletCenterPosition[kmaxBullet];

	// �e�����˂�������
	float bulletDirection[kmaxBullet];

	// �e�̔��˃X�s�[�h
	float bulletSpeed;

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

	/// ����֘A
	// ����̃T�C�Y
	Point weaponSize;

	// ����̃e�N�X�`���T�C�Y
	Point weaponTextureSize;

	// �s���O����T�C�Y
	Point prevWeaponSize;
	// �s���㕐��T�C�Y
	Point nextWeaponSize;

	/// �e�֘A
	// �e�̃e�N�X�`���T�C�Y
	Point bulletTextureSize;

	// �e�̃T�C�Y
	Point bulletSize;

	/******** �s���֘A **********/
	/// �{�X�֘A
	// ����������Ă��邩
	bool init;

	// �U������
	bool inAction;
	// �U�����I�����Ă��邩
	bool endAction;

	// �X�^������
	bool inStun;
	// �X�^�����鎞��
	int stunTime;

	// �_���[�W���󂯂Ă���̂�
	bool inDamage;

	// �j���������Ă��邩
	bool coreSeparated;

	// �e�֘A
	// �e��������Ă��邩
	bool isShot[kmaxBullet];

	// �e�̐�������
	float bulletAliveTime[kmaxBullet];

	/******** �C�[�W���O�֘A **********/
	// �C�[�W���O�pt
	float t = 0.0f;

};