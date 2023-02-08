#include "Class/SceneManager/Scene/Title.h"

// �R���X�g���N�^
Title::Title() {
	Initialize();
}
// �f�X�g���N�^
Title::~Title() {

}



// ������
void Title::Initialize() {
	nextScene = sceneNone;
	Novice::SetWindowMode(kFullscreen);
	reticlePosition = { 1000,800 };
	preMousePosition = BaseInput::GetMousePosition();
	isToPlay = false;
	isToEnd = false;
}
// �X�V
void Title::Update() {

	// ���[���h���W�ɖ߂����v�Z
	Point rightStick;
	BaseInput::GetControllerRightJoysState(&rightStick);
	int x, y;
	Novice::GetMousePosition(&x, &y);
	// �}�E�X�������Ă��鎞
	if (preMousePosition.x != x || preMousePosition.y != y) {
		reticlePosition = BaseInput::GetMousePosition();
	}
	// �X�e�B�b�N�����͂���Ă��鎞
	if (BaseMath::GetLength(rightStick) != 0.0f) {
		reticlePosition.x += 20 * rightStick.x;
		reticlePosition.y += 20 * rightStick.y;
	}
	// �Ə�����ʓ��Ɏ��߂�
	if (reticlePosition.x < BaseConst::kPlayerReticleSize) {
		reticlePosition.x = BaseConst::kPlayerReticleSize;
	}
	else if (BaseConst::kWindowWidth - BaseConst::kPlayerReticleSize < reticlePosition.x) {
		reticlePosition.x = BaseConst::kWindowWidth - BaseConst::kPlayerReticleSize;
	}
	if (reticlePosition.y < BaseConst::kPlayerReticleSize) {
		reticlePosition.y = BaseConst::kPlayerReticleSize;
	}
	else if (BaseConst::kWindowHeight - BaseConst::kPlayerReticleSize < reticlePosition.y) {
		reticlePosition.y = BaseConst::kWindowHeight - BaseConst::kPlayerReticleSize;
	}

	// �u�X�^�[�g�v�̒��Ƀ}�E�X������ꍇ
	if (BaseConst::kTitletoPlayLeftTop.x < reticlePosition.x && reticlePosition.x < BaseConst::kTitletoPlayRightBottom.x &&
		BaseConst::kTitletoPlayLeftTop.y < reticlePosition.y && reticlePosition.y < BaseConst::kTitletoPlayRightBottom.y) {
		isToPlay = true;
		if (BaseInput::GetMouseState(LeftClick, Trigger) ||
			BaseInput::GetControllerState(kControllerButtonL2A, Trigger) ||
			BaseInput::GetControllerState(kControllerButtonR2B, Trigger)) {
			nextScene = sceneTutorialStage;
		}
	}
	else {
		isToPlay = false;
	}
	if (BaseConst::kTitletoEndLeftTop.x < reticlePosition.x && reticlePosition.x < BaseConst::kTitletoEndRightBottom.x &&
		BaseConst::kTitletoEndLeftTop.y < reticlePosition.y && reticlePosition.y < BaseConst::kTitletoEndRightBottom.y) {
		isToEnd = true;
		if (BaseInput::GetMouseState(LeftClick, Trigger) ||
			BaseInput::GetControllerState(kControllerButtonL2A, Trigger) ||
			BaseInput::GetControllerState(kControllerButtonR2B, Trigger)) {
			Initialize();
		}
	}
	else {
		isToEnd = false;
	}





	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger)) {
		nextScene = sceneTutorialStage;
	}

}
// �`��
void Title::Draw() {
	Novice::DrawSprite(0, 0, BaseTexture::kBackGround[0], 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(0, 0, BaseTexture::kBackGround[1], 1, 1, 0.0f, WHITE);
	Novice::DrawBox(0, 0, BaseConst::kWindowWidth, BaseConst::kWindowHeight, 0.0f, 0x00000077, kFillModeSolid);
	Novice::DrawSprite(0, 0, BaseTexture::kBackGround[2], 1, 1, 0.0f, WHITE);
	Novice::DrawBox(0, 0, BaseConst::kWindowWidth, BaseConst::kWindowHeight, 0.0f, 0xFFFFFF22, kFillModeSolid);
	Novice::DrawSprite(0, 0, BaseTexture::kUserInterfaceTitle[0], 1, 1, 0.0f, WHITE);

	Novice::SetBlendMode(kBlendModeAdd);
	if (isToPlay) {
		Novice::DrawBox(
			BaseConst::kTitletoPlayLeftTop.x - BaseConst::kSelectPadding, BaseConst::kTitletoPlayLeftTop.y - BaseConst::kSelectPadding,
			BaseConst::kTitletoPlayRightBottom.x - BaseConst::kTitletoPlayLeftTop.x + BaseConst::kSelectPadding * 2,
			BaseConst::kTitletoPlayRightBottom.y - BaseConst::kTitletoPlayLeftTop.y + BaseConst::kSelectPadding * 2,
			0.0f, 0x00AAAAFF, kFillModeSolid
		);
	}
	if (isToEnd) {
		Novice::DrawBox(
			BaseConst::kTitletoEndLeftTop.x - BaseConst::kSelectPadding, BaseConst::kTitletoEndLeftTop.y - BaseConst::kSelectPadding,
			BaseConst::kTitletoEndRightBottom.x - BaseConst::kTitletoEndLeftTop.x + BaseConst::kSelectPadding * 2,
			BaseConst::kTitletoEndRightBottom.y - BaseConst::kTitletoEndLeftTop.y + BaseConst::kSelectPadding * 2,
			0.0f, 0x00AAAAFF, kFillModeSolid
		);
	}
	Novice::SetBlendMode(kBlendModeNormal);

	if (isToPlay || isToEnd) {
		Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 10, 10, 0.0f, 0xFF0000FF, kFillModeWireFrame);
		Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 13, 13, 0.0f, 0xFF0000FF, kFillModeWireFrame);
	}
	else {
		Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 10, 10, 0.0f, 0x00FF00FF, kFillModeWireFrame);
		Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 13, 13, 0.0f, 0x00FF00FF, kFillModeWireFrame);
	}
	Novice::ScreenPrintf(1920 / 2, 1080 / 2, "Title");
	Novice::ScreenPrintf(1920 / 2, 1080 / 2 + 20, "Push Space to next");
}