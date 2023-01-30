#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/ObjectManager.h"
#include "Class/Wire/WireManager.h"
#include "Class/AttackHitBox/EnemyAttackHitBox.h"

/*********************************************
 * �{�X�N���X
 *
 * �{�X�֘A�̍s�����ׂĂ��Ǘ�����N���X
 *********************************************/

class ObjectManager;
class Object;
class WireManager;

class Boss {
public:

	// �R���X�g���N�^
	Boss();

	// �f�X�g���N�^
	~Boss();

	// ������
	void Initialize(ObjectManager* objectManager);

	// �X�V����
	void Update(Point playerPosition, ObjectManager* objectManager,WireManager* wireManager);

	// �`�揈��
	void Draw();

	// �{�X���̂̓����蔻���Ԃ��֐�
	// �Ԃ�l�F�������Ă��� ... true �������Ă��Ȃ� ... false
	// �����F
	// hitPosition ... �����������W
	// �����Ŏw�肵��Point���{�X�̊O�k�ɖ������Ă��邩�ǂ�����Ԃ��֐�
	bool GetBossCollision(Point hitPosition);

private:

	/*********************************
		�����o�֐�
	*********************************/

	/******** �ϊ��֐� **********/
	// �{�X���摜�̍��W�����߂�
	Point GetLCoverPosition(Point centerPosition);
	// �{�X�E�摜�̍��W�����߂�
	Point GetRCoverPosition(Point centerPosition);

	// �{�X���摜�̓����蔻������߂�
	Point GetLCoverCollision(Point centerPosition);
	// �{�X�E�摜�̓����蔻������߂�
	Point GetRCoverCollision(Point centerPosition);

	// ����摜�̑��΍��W�����߂�
	Point GetWeaponPosition(Point centerPosition);

	// ���˒n�_�̑��΍��W�����߂�
	Point GetShotPosition(Point centerPosition);

	// �����t�b�N�̑��΍��W�����߂�
	Point GetLHookPosition(Point centerPosition);

	// �E���t�b�N�̑��΍��W�����߂�
	Point GetRHookPosition(Point centerPosition);

	/******** �f�o�b�O�֐� **********/
	void Debug();

	/******** �s���֐� **********/
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

	// �o�C�u���[�V�����֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// shakeStrength ... �V�F�C�N����ۂ̋���
	// vibTime ... �U������b��
	// vibRate ... �U������Ԋu
	// vibValue ... �U������������
	// ���Ԋu�ŁA���b���U��������֐�
	void vibration(int shakeStrength, float vibTime, float vibRate, int vibValue);

	/// <summary>
	/// �퓬�J�n���̃A�j���[�V�������Đ�����֐�
	/// </summary>
	/// <param name="vibTime">�U�����鎞��</param>
	/// <param name="closeTime1">�{�X���r���܂ŕ���̂ɂ����鎞��</param>
	/// <param name="roarTime">���K���鎞��</param>
	/// <param name="closeTime2">�{�X�����S�ɕ��鎞��</param>
	void PlayStartAnim(float vibTime, float closeTime1, float roarTime, float closeTime2);

	// �s���Ȃ��֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// waitTime ... �ҋ@����b��
	// �s���̍��Ԃɋ��ފ֐��B
	void None(float waitFrame);

	// �ڋߊ֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// playerPosition ... �v���C���[���S���W
	// moveTIme ... ��]���鎞��
	// afterWaitTime ... �s����ɔ�������ҋ@����
	// �v���C���[�Ɍ������Đڋ߂���֐�
	void Approach(Point playerPosition, float moveTime, float afterWaitTime, WireManager* wireManager);

	// �����֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// playerPosition ... �v���C���[���S���W
	// moveTIme ... ��]���鎞�ԁB����͕b��
	// afterWaitTime ... �s����ɔ�������ҋ@����
	// �v���C���[�Ɍ������ė�������֐�
	void Separation(Point playerPosition, float moveTime,float afterWaitTime, WireManager* wireManager);

	// ��]�֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// endDegree ... �I�����̊p�x
	// rotateTime ... ��]���鎞�ԁB����͕b��
	// afterWaitTime ... �s����ɔ�������ҋ@����
	// �{�X����]������֐�
	void Rotate(float endDegree, float RotateTime, float afterWaitTime, WireManager* wireManager);

	// �ːi�֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// playerPosition ... �v���C���[�̍��W
	// readyTime ... �ːi�̏����ɂ�����b��
	// chargeTime ... �ːi�̗��߂ɂ�����b��
	// rushTime ... �ːi�ɂ�����b��
	// backTime ... �߂鎞�ɂ�����b��
	// afterWaitTime ... �s����ɔ�������ҋ@����
	// damage ... �s���ɂ���Ĕ�������_���[�W
	// �{�X���v���C���[�̌����ɓːi������֐�
	void Rush(Point playerPosition, float readyTime , float chargeTime, float rushTime, float backTime, float afterWaitTime, float damage, WireManager* wireManager);

	// �a���֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// playerPosition ... �v���C���[�̍��W
	// readyTime ... �{�X���J���܂łɂ�����b��
	// deployTime ... �u���[�h�̓W�J�ɂ�����b��
	// preparationTime�@... �U���܂ł̑ҋ@����
	// rushTime ... �ːi�ɂ�����b��
	// backTime ... �߂鎞�ɂ�����b��
	// afterWaitTime ... �s����ɔ�������ҋ@����
	// damage ... �s���ɂ���Ĕ�������_���[�W
	// �{�X���a�����s���֐�
	void Slash(Point playerPosition, float readyTime, float deployTime, float preparationTime, float slashTime, float backTime, float afterWaitTIme, float damage, WireManager* wireManager);
	
	// �ˌ��֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// playerPosition ... �v���C���[�̍��W
	// readyTime ... �{�X���J���܂łɂ�����b��
	// deployTime ... �e�̓W�J�ɂ�����b��
	// preparationTime�@... �U���܂ł̑ҋ@����
	// shotTime ... �ˌ��b��
	// backTime ... �߂鎞�ɂ�����b��
	// afterWaitTime ... �s����ɔ�������ҋ@����
	// fireRate ... ���b�����Ɏˌ����邩
	// damage ... �s���ɂ���Ĕ�������_���[�W
	// �{�X���ˌ����s���֐�
	void Shot(Point playerPosition, float readyTime, float deployTime, float preparationTime, float shotTime, float backTime, float afterWaitTime, float fireRate, float damage, WireManager* wireManager);

	// �I�u�W�F�N�g�����֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// readyTime ... �{�X�̍��W�𒆐S�ɖ߂��b��
	// deployTime ... �U�������ɂ�����b��
	// rushTime�@... �V��ɓːi����܂łɂ�����b��
	// standByTime ... �ҋ@�b��
	// backTime ... �߂鎞�ɂ�����b��
	// damage ... �s���ɂ���Ĕ�������_���[�W
	// �{�X���V��ɂԂ���A�j�Ђ𗎉������čU�����s���֐�
	void Fall(float readyTime, float deployTime, float rushTime, float standByTime, float backTime, float afterWaitTime, float damage, WireManager* wireManager);

	/******** �X�^���֐� **********/
	// �X�^���֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// readyTime ... �X�^�����n�߃��[�V�����b��
	// deployTime ... �X�^�����n�߃��[�V�����b��
	// stanTime�@... �X�^���b��
	// backTime ... �߂鎞�ɂ�����b��
	// �w�肳�ꂽ�b���{�X���X�^������֐�
	void Stun(float readyTime, float deployTime, float stanTime, float backTime, WireManager* wireManager);

	/******** �_���[�W **********/
	// �_���[�W�֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// readyTime ... �X�^�����n�߃��[�V�����b��
	// deployTime ... �X�^�����n�߃��[�V�����b��
	// stanTime�@... �X�^���b��
	// backTime ... �߂鎞�ɂ�����b��
	// �{�X�ɑ΂��ă_���[�W���^�������Ԃɂ���֐�
	void MakeDamagePossible(float readyTime, float deployTime, float openTime, float stanTime, float backTime, float closeTime, WireManager* wireManager, ObjectManager* objectManager);

	/******** �_���[�W�A�j���[�V���� **********/
	// �_���[�W�A�j���[�V�����֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// readyTime ... �U�����鎞��
	// shakeStrength ... �U�����鋭��
	// �_���[�W���^����ꂽ���̃A�j���[�V�������Đ�����֐�
	void playTakeDamageAnim(float animTime, float shakeStrength);

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
		FALL, // �I�u�W�F�N�g�����U��
		APPROACH, // �ڋ�
		SEPARATION // ����
	};
	// �U���p�^�[�����i�[����int�^�ϐ�
	int attackPattern = NONE;
	int prevAttackPattern[2] = { NONE };

	/******** �s�����Ԓn�_�iEnum�j **********/
	// �U����X�^�����̒��Ԓn�_���B�̍ۂɐ؂�ւ�
	enum ActionWayPoint 
	{
		WAYPOINT0, // ������
		WAYPOINT1, // �s�����Ԓn�_�`
		WAYPOINT2,
		WAYPOINT3,
		WAYPOINT4,
		WAYPOINT5,
		WAYPOINT6
	};
	//�s�����ǂ��܂Ői��ł��邩���i�[����ϐ�
	int actionWayPoint = WAYPOINT0;

	/******** �s������(Enum) **********/
	// �s���������_���ɕ��򂳂���B�����l��Pattern1
	enum ActionBranch {
		Pattern1, //�s������ 1~
		Pattern2,
		Pattern3,
		Pattern4,
		Pattern5
	};
	// �s�����ɂǂ̍s���ɕ��򂳂��邩���i�[����ϐ�
	int actionBranch = Pattern1;

	// �U�����ɂǂ̍U���ɕ��򂳂��邩���i�[����ϐ�
	int attackBranch = Pattern1;

	float waitTime;

	bool pleaseWait;

	/******** HP�֘A **********/
	// HP(�����ŏ�����)
	const float MaxHP = 5.0f;
	float HP;

	/******** �_���[�W�֘A **********/
	// �{�X���̂̃_���[�W
	float bodyDamage;

	// ���̃_���[�W
	float bladeDamage;

	// �e�̃_���[�W
	float bulletDamage[kmaxBullet];

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

	// 1�t���[���O�̊p�x
	int beforeDegree;

	// �s���O�I�t�Z�b�g
	int prevOffset;
	// �s����I�t�Z�b�g
	int nextOffset;

	// �Q�Ƃ���v���C���[���W
	Point prePlayerPosition;

	// �v���C���[�Ƃ̋���
	float playerDistance;
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
	Point coreTextureSize;

	// �t�b�N�̃e�N�X�`���T�C�Y
	Point hookTextureSize;

	// �T�C�Y
	Point size;
	// �j�̃T�C�Y
	Point coreSize;

	// �t�b�N�̃T�C�Y
	Point hookSize;

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
	// �o�C�u���[�V�����������̍ۂɗp������ϐ�
	bool vibInit;

	// �퓬���J�n���Ă��邩
	bool isBattleStart;

	// �U������
	bool inAction;
	// �U�����I�����Ă��邩
	bool endAction;

	// �X�^������
	bool inStun;
	// �X�^�����鎞��
	int stunTime;

	// �_���[�W���󂯂����ԂȂ̂�
	bool canTakeDamage;

	// �_���[�W���󂯂���
	bool inDamage;

	// �j���������Ă��邩
	bool coreSeparated;

	// �{�X�����S���Ă��邩
	bool inDead;

	// �e�֘A
	// �e��������Ă��邩
	bool isShot[kmaxBullet];

	// �e�̐�������
	float bulletAliveTime[kmaxBullet];

	/// �I�u�W�F�N�g�֘A

	// �I�u�W�F�N�g�𐶐����邩�ǂ���
	bool canGeneratedBlock = false;

	// �I�u�W�F�N�g������
	int generatedBlockValue = 0;

	// �I�u�W�F�N�g�����Ԋu
	float generatedBlockInterval = 0.0f;

	/******** �C�[�W���O�֘A **********/
	// �C�[�W���O�pt
	float t = 0.0f;

	// �\���pt ���t�Ƃ͕ʂ�t���g���������Ɏg��
	float spareT = 0.0f;

	// �t�b�N�̃I�u�W�F�N�g
	Object* hook[2];

	// �j�p�t�b�N
	Object* core;

};