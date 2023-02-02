#pragma 
#include "MyBase/Resource/BaseConst.h"
#include "MyBase/Define/BaseEnum.h"
#include "MyBase/Define/BaseStruct.h"
#include "MyBase/Resource/BaseTexture.h"

#include <Novice.h>


///////////////////////////////////////////////
/* - �Q�[�����Ŏg���S�Ă̓��͑�����Ǘ�����N���X - */
///////////////////////////////////////////////


class BaseInput
{

public: // �����o�֐�

	// ������
	static void Initialize();
	// �X�V
	static void Update();
	// �`��
	static void Draw();



	// �}�E�X���W���󂯎��֐�
	// �Ԃ�l�F�}�E�X���W��Point
	// �����F����
	// �}�E�X�̍��W��Point�^�Ŏ󂯎��֐�
	static Point GetMousePosition();


	// �}�E�X�̓��͏�Ԃ��󂯎��֐�
	// �Ԃ�l�Fkey �� state �̏ꍇ -> true �����łȂ��ꍇ -> false
	// �����F
	// key ... ���؂���L�[
	// state ... ���؂��������
	// ����̃L�[���ǂ�ȏ�ԁiNull,Trigger,Press,Release�j�����`�F�b�N����֐�
	static bool GetMouseState(MouseButton key, InputState state);


	// �L�[�̓��͏�Ԃ��󂯎��֐�
	// �Ԃ�l�Fkey �� state �̏ꍇ -> true �����łȂ��ꍇ -> false
	// �����F
	// key ... ���؂���L�[
	// state ... ���؂��������
	// ����̃L�[���ǂ�ȏ�ԁiNull,Trigger,Press,Release�j�����`�F�b�N����֐�
	static bool GetKeyboardState(int key, InputState state);


	/// <summary>
	/// ����̃L�[���ǂ�ȏ�ԁiNull,Trigger,Press,Release�j�����`�F�b�N����֐�
	/// �{�^���̓��͏�Ԃ��󂯎��֐�
	/// </summary>
	/// <param name="key">���؂���{�^��</param>
	/// <param name="state">���؂��������</param>
	/// <returns>key �� state �̏ꍇ -> true �����łȂ��ꍇ -> false</returns>
	static bool GetControllerState(ControllerButton key, InputState state);

	/// <summary>
	/// �R���g���[���[�̃X�e�B�b�N�̏�Ԃ��󂯎��֐�
	/// </summary>
	/// <param name="left">���X�e�B�b�N</param>
	/// <param name="right">�E�X�e�B�b�N</param>
	/// <returns>����Ɏ󂯎�ꂽ�ꍇ true</returns>
	static void GetControllerJoysState(Point* left, Point* right);
	static void GetControllerLeftJoysState(Point* left);
	static void GetControllerRightJoysState(Point* right);

	/// <summary>
	/// �A�i���O�X�e�B�b�N�� 100% - 0% �ŕ\���֐�
	/// </summary>
	/// <param name="p">�A�i���O�X�e�B�b�N�̓��͒l</param>
	/// <returns>�X���� %</returns>
	static float AnalogToPer(int p);

	// �}�E�X���t�H�[���ɌŒ肷��֐�
	// �Ԃ�l�F����
	// �����F����
	// �}�E�X���t�H�[�����ɌŒ肷��֐�
	static void ClipMouseinFoam();


	// �}�E�X�����͈͂ɌŒ肷��֐�
	// �Ԃ�l�F����
	// �����F
	// position ... �Œ肷��N���C�A���g���W�ix,y�j
	// length ... �Œ肷��͈́iwidth,height�j
	// �}�E�X�����͈̔͂ɌŒ肷��֐�
	static void ClipMouseinRectangle(Point position, Point length);


	// �Œ肵���}�E�X���������֐�
	// �Ԃ�l�F����
	// �����F����
	// �}�E�X�̌Œ����������֐��B�Œ肵����͕K���Ăяo�����ƁI�I�I�I�I
	static void ClipMouseClear();


private: // �����o�ϐ�

	// �}�E�X���W
	static Point mousePosition;

	// �L�[�̓��͏󋵁i����̃t���[���j
	static char keys[];
	// �L�[�̓��͏󋵁i�O��̃t���[���j
	static char preKeys[];

	// �{�^���̓��͏� (����̃t���[��)
	static bool buttons[];
	// �{�^���̓��͏� (�O��̃t���[��)
	static bool preButtons[];


};

