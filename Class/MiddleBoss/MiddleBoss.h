#include "MyBase/MyBase.h"
#include "Class/Object/ObjectManager.h"
#include "Class/Wire/WireManager.h"
#include "Class/AttackHitBox/EnemyAttackHitBox.h"
#include "Class/PublicFlag/PublicFlag.h"

/*********************************************
 * ���{�X�N���X
 *
 * ���{�X�֘A�̍s�����ׂĂ��Ǘ�����N���X
 *********************************************/

class ObjectManager;
class Object;
class WireManager;

class MiddleBoss {
public:

	// �R���X�g���N�^
	MiddleBoss();

	// ������
	void Initialize(ObjectManager* objectManager);

	// �X�V����
	void Update(Point playerPosition, ObjectManager* objectManager, WireManager* wireManager);

	// �`�揈��
	void Draw();

private:

	/*********************************
		�����o�֐�
	*********************************/

	//�C�[�Y�A�E�g�iInt�^�j
	int IntEaseOut(float t, long int b, long int c, float d) {
		float easeT = 1.0f - powf(1.0f - t / d, 3.0f);
		return (1.0f - easeT) * b + easeT * c;
	}

	// �J���[�C�[�W���O
	unsigned int ColorEasing(float t, unsigned int startColor, unsigned int endColor, float easingTime) {
		unsigned int red = IntEaseOut(t, (((startColor & 0xFF000000) >> 24) & 0xFF), (((endColor & 0xFF000000) >> 24) & 0xFF), easingTime);
		unsigned int green = IntEaseOut(t, (((startColor & 0x00FF0000) >> 16) & 0xFF), (((endColor & 0x00FF0000) >> 16) & 0xFF), easingTime);
		unsigned int blue = IntEaseOut(t, (((startColor & 0x0000FF00) >> 8) & 0xFF), (((endColor & 0x0000FF00) >> 8) & 0xFF), easingTime);
		unsigned int alpha = IntEaseOut(t, (((startColor & 0x000000FF)) & 0xFF), (((endColor & 0x000000FF)) & 0xFF), easingTime);

		return (red << 24) + (green << 16) + (blue << 8) + alpha;
	}

	// ����摜�̑��΍��W�����߂�
	Point GetWeaponPosition(Point centerPosition);

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
	/// �{�X��̊J�n���̃A�j���[�V�����֐�
	/// </summary>
	/// <param name="cameraMoveTime">�J�����𓮂�������</param>
	/// <param name="appearTime">�{�X���ォ��o������</param>
	/// <param name="roarTime">���K����</param>
	/// <param name="waitTime">�J�������߂鎞��</param>
	void PlayStartAnim(float cameraMoveTime, float appearTime, float roarTime, float waitTime);

	/// <summary>
	/// ���S���̃A�j���[�V�������Đ�����֐�
	/// </summary>
	/// /// <param name="cameraMoveTime">�J�����𓮂�������</param>
	/// <param name="roarTime">���K����</param>
	/// <param name="moveTime">�������ɍs��</param>
	/// <param name="runAwayTime">�����ď��</param>
	/// <param name="cameraBackTime">�J������߂�</param>
	void PlayDeadAnim(float cameraMoveTime, float moveTime,float runAwayTime,float cameraBackTime, WireManager* wireManager);

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
	void Separation(Point playerPosition, float moveTime, float afterWaitTime, WireManager* wireManager);

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
	void Rush(Point playerPosition, float readyTime, float chargeTime, float rushTime, float backTime, float afterWaitTime, float damage, WireManager* wireManager);

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

	/******** �_���[�W�A�j���[�V���� **********/
	// �_���[�W�A�j���[�V�����֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// readyTime ... �U�����鎞��
	// shakeStrength ... �U�����鋭��
	// �_���[�W���^����ꂽ���̃A�j���[�V�������Đ�����֐�
	void playTakeDamageAnim(float animTime, float shakeStrength);

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

	// �s���Ԃ̑ҋ@����
	float waitTime;

	// �ҋ@���邩
	bool pleaseWait;

	// ���݉��o����
	// �J�n�A�j���[�V����
	bool isPlayingStartAnim;
	// ���S�A�j���[�V����
	bool isPlayingDeadAnim;

	// ���S�A�j���[�V�������I�����Ă��邩
	bool isEndDeadAnim;

	/******** HP�֘A **********/
	// HP(�����ŏ�����)
	const float MaxHP = 10.0f;
	float HP;

	/******** �_���[�W�֘A **********/
	// �{�X���̂̃_���[�W
	float bodyDamage;

	// ���̃_���[�W
	float bladeDamage;

	/******** ���W�֘A **********/
	/// �{�X�֘A
	// ���S���W
	Point centerPosition;
	// �V�F�C�N����Ƃ��̍��W�̕ω���
	Point shakeVariation;
	// �V�F�C�N����͈�
	int shakeRange;

	// �{�X�̉�]�p�idegree���j
	int degree;

	// ��ʒ����̍��W
	Point screenCenterPosition;

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

	// �Q�Ƃ���v���C���[���W
	Point prePlayerPosition;

	// �v���C���[�Ƃ̋���
	float playerDistance;
	// �v���C���[�ւ̕���
	float playerDirection;

	// �J�b�g�V�[���p�J�����ړ��O���W
	Point prevScreenPosition;

	// �J�b�g�V�[���p�J�����ړ�����W
	Point nextScreenPosition;

	// �u���b�N�����p���W
	Point blockSpawnPoint;

	/******** �T�C�Y�֘A **********/
	/// �{�X�֘A

	// �e�N�X�`���T�C�Y
	Point textureSize;
	// �T�C�Y
	Point size;

	/// ����֘A

	// ����̃T�C�Y
	Point weaponSize;

	// ����̃e�N�X�`���T�C�Y
	Point weaponTextureSize;

	// �s���O����T�C�Y
	Point prevWeaponSize;
	// �s���㕐��T�C�Y
	Point nextWeaponSize;

	/******** �s���֘A **********/
	/// �{�X�֘A
	// ����������Ă��邩
	bool init;
	// �o�C�u���[�V�����������̍ۂɗp������ϐ�
	bool vibInit;

	// �U�����Đ����Ǘ�����
	bool isVibPlaySound;

	// �퓬���J�n���邩
	bool doBattleStart;

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

	// �_���[�W���󂯂���
	bool inDamage;
	// �_���[�W���󂯂����Ԃ�
	bool canTakeDamage;

	// �{�X�����S���Ă��邩
	bool inDead;

	/// �I�u�W�F�N�g�֘A

	// �I�u�W�F�N�g�𐶐����邩�ǂ���
	bool canGeneratedBlock = false;

	// �I�u�W�F�N�g������
	int generatedBlockValue = 0;

	// �I�u�W�F�N�g�����Ԋu
	float generatedBlockInterval = 0.0f;

	// �G�𐶐����邩�ǂ���
	bool canGeneratedEnemy = false;

	// �G������
	int generatedEnemyValue = 0;

	// �G�����Ԋu
	float generatedEnemyInterval = 0.0f;


	/******** �C�[�W���O�֘A **********/
	// �C�[�W���O�pt
	float t = 0.0f;

	// �\���pt ���t�Ƃ͕ʂ�t���g���������Ɏg��
	float spareT = 0.0f;

	// �����蔻��
	Object* core;

	/******** �F�֘A **********/
	// �k�̐F
	unsigned int color;

	// �s���O�F
	unsigned int prevColor;
	// �s����F
	unsigned int nextColor;

	/// ���֌W
	// ���K��
	int screamSoundHundle;
	int screamVoiceHundle;

};