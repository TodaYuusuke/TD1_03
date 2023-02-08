#include "Class/SceneManager/Scene/GameClear.h"

// �R���X�g���N�^
GameClear::GameClear() {
	Initialize();
}
// �f�X�g���N�^
GameClear::~GameClear() {

}



// ������
void GameClear::Initialize() {

	nextScene = sceneNone;

	PublicFlag::Initialize();
	BaseDraw::SetScreenPosition({ 0,1080 });

	reticlePosition = { 1000,800 };
	preMousePosition = BaseInput::GetMousePosition();
	isToTitle = false;
	isToEnd = false;

	isSelected = false;

	feedInFlame = kFeedInMax;
	feedOutFlame = kFeedOutMax;

	// BGM�Đ�
	if (Novice::IsPlayingAudio(bgmHandle) == 0 || bgmHandle == -1) {
		//bgmHandle = Novice::PlayAudio(BaseAudio::, true, 0.1f);
	}
}
// �X�V
void GameClear::Update() {
	if (0 < feedInFlame) {
		feedInFlame--;
	}

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
	if (!isSelected) {
		// �u�X�^�[�g�v�̒��Ƀ}�E�X������ꍇ
		if (BaseConst::kGameCleartoPlayLeftTop.x < reticlePosition.x && reticlePosition.x < BaseConst::kGameCleartoPlayRightBottom.x &&
			BaseConst::kGameCleartoPlayLeftTop.y < reticlePosition.y && reticlePosition.y < BaseConst::kGameCleartoPlayRightBottom.y) {
			if (!Novice::IsPlayingAudio(BaseAudio::kSelect) && !isToTitle) {
				Novice::PlayAudio(BaseAudio::kSelect, 0, BaseAudio::SEvolume);
			}
			isToTitle = true;
			if (BaseInput::GetMouseState(LeftClick, Trigger) ||
				BaseInput::GetControllerState(kControllerButtonL2A, Trigger) ||
				BaseInput::GetControllerState(kControllerButtonR2B, Trigger)) {
				isSelected = true;
				feedOutFlame = kFeedOutMax;
				Novice::PlayAudio(BaseAudio::kSpecialDecide, 0, BaseAudio::SEvolume);
			}
		}
		else {
			isToTitle = false;
		}
		if (BaseConst::kGameCleartoEndLeftTop.x < reticlePosition.x && reticlePosition.x < BaseConst::kGameCleartoEndRightBottom.x &&
			BaseConst::kGameCleartoEndLeftTop.y < reticlePosition.y && reticlePosition.y < BaseConst::kGameCleartoEndRightBottom.y) {
			if (!Novice::IsPlayingAudio(BaseAudio::kSelect) && !isToEnd) {
				Novice::PlayAudio(BaseAudio::kSelect, 0, BaseAudio::SEvolume);
			}
			isToEnd = true;
			if (BaseInput::GetMouseState(LeftClick, Trigger) ||
				BaseInput::GetControllerState(kControllerButtonL2A, Trigger) ||
				BaseInput::GetControllerState(kControllerButtonR2B, Trigger)) {
				isSelected = true;
				feedOutFlame = kFeedOutMax;
				Novice::PlayAudio(BaseAudio::kDecide, 0, BaseAudio::SEvolume);
			}
		}
		else {
			isToEnd = false;
		}
	}
	else {
		feedOutFlame--;
		if (feedOutFlame <= 0) {

			if (isToTitle) {
				nextScene = sceneTitle;
			}
			else if (isToEnd) {
				nextScene = sceneEnd;
			}
		}
	}





	//if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger)) {
	//	nextScene = sceneTutorialStage;
	//}

}
// �`��
void GameClear::Draw() {
	Novice::DrawSprite(0, 0, BaseTexture::kBackGround[0], 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(0, 0, BaseTexture::kBackGround[1], 1, 1, 0.0f, WHITE);
	Novice::DrawBox(0, 0, BaseConst::kWindowWidth, BaseConst::kWindowHeight, 0.0f, 0x00000077, kFillModeSolid);
	Novice::DrawSprite(0, 0, BaseTexture::kBackGround[2], 1, 1, 0.0f, WHITE);
	Novice::DrawBox(0, 0, BaseConst::kWindowWidth, BaseConst::kWindowHeight, 0.0f, 0xFFFFFF22, kFillModeSolid);
	Novice::DrawSprite(0, 0, BaseTexture::kUserInterfaceGameClear, 1, 1, 0.0f, WHITE);

	Novice::SetBlendMode(kBlendModeAdd);
	if (isToTitle) {
		Novice::DrawBox(
			BaseConst::kGameCleartoPlayLeftTop.x - BaseConst::kSelectPadding, BaseConst::kGameCleartoPlayLeftTop.y - BaseConst::kSelectPadding,
			BaseConst::kGameCleartoPlayRightBottom.x - BaseConst::kGameCleartoPlayLeftTop.x + BaseConst::kSelectPadding * 2,
			BaseConst::kGameCleartoPlayRightBottom.y - BaseConst::kGameCleartoPlayLeftTop.y + BaseConst::kSelectPadding * 2,
			0.0f, 0x00AAAAFF, kFillModeSolid
		);
	}
	if (isToEnd) {
		Novice::DrawBox(
			BaseConst::kGameCleartoEndLeftTop.x - BaseConst::kSelectPadding, BaseConst::kGameCleartoEndLeftTop.y - BaseConst::kSelectPadding,
			BaseConst::kGameCleartoEndRightBottom.x - BaseConst::kGameCleartoEndLeftTop.x + BaseConst::kSelectPadding * 2,
			BaseConst::kGameCleartoEndRightBottom.y - BaseConst::kGameCleartoEndLeftTop.y + BaseConst::kSelectPadding * 2,
			0.0f, 0x00AAAAFF, kFillModeSolid
		);
	}
	Novice::SetBlendMode(kBlendModeNormal);

	// ���S
	//Novice::DrawSprite(350, 230, BaseTexture::kUserInterfaceGameClear[1], 1, 1, 0.0f, WHITE);

	float x = 200;
	BaseDraw::DrawSprite({ x,200 - 64 * 3 }, BaseTexture::kBlockTexture, { 1,1 }, 0.0f, WHITE);
	BaseDraw::DrawSprite({ x,200 - 64 * 2 }, BaseTexture::kBlockTexture, { 1,1 }, 0.0f, WHITE);
	BaseDraw::DrawSprite({ x,200 - 64 }, BaseTexture::kBlockTexture, { 1,1 }, 0.0f, WHITE);
	BaseDraw::DrawSprite({ x,200 }, BaseTexture::kBlockTexture, { 1,1 }, 0.0f, WHITE);
	
	BaseDraw::DrawSprite({ x - 64,180 - 64 * 3 }, BaseTexture::kBlockTexture, { 1,1 }, 0.0f, WHITE);
	BaseDraw::DrawSprite({ x - 64,180 - 64 * 2 }, BaseTexture::kBlockTexture, { 1,1 }, 0.0f, WHITE);
	BaseDraw::DrawSprite({ x - 64,180 - 64 }, BaseTexture::kBlockTexture, { 1,1 }, 0.0f, WHITE);
	BaseDraw::DrawSprite({ x - 64,180 }, BaseTexture::kBlockTexture, { 1,1 }, 0.0f, WHITE);
	
	BaseDraw::DrawSprite({ x + 64,150 - 64 * 3 }, BaseTexture::kBlockTexture, { 1,1 }, 0.0f, WHITE);
	BaseDraw::DrawSprite({ x + 64,150 - 64 * 2 }, BaseTexture::kBlockTexture, { 1,1 }, 0.0f, WHITE);
	BaseDraw::DrawSprite({ x + 64,150 - 64 }, BaseTexture::kBlockTexture, { 1,1 }, 0.0f, WHITE);
	BaseDraw::DrawSprite({ x + 64,150 }, BaseTexture::kBlockTexture, { 1,1 }, 0.0f, WHITE);
						   

	BaseDraw::DrawSprite({ x,300 }, BaseTexture::kRPlayerIdle, { 1,1 }, 0.0f, WHITE);

	// �Ə�
	if (isToTitle || isToEnd) {
		Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 10, 10, 0.0f, 0xFF0000FF, kFillModeWireFrame);
		Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 13, 13, 0.0f, 0xFF0000FF, kFillModeWireFrame);
	}
	else {
		Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 10, 10, 0.0f, 0x00FF00FF, kFillModeWireFrame);
		Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 13, 13, 0.0f, 0x00FF00FF, kFillModeWireFrame);
	}

	Novice::DrawBox(0, 0, BaseConst::kWindowWidth, BaseConst::kWindowHeight, 0.0f, 0xFFFFFF00 + (255 / kFeedOutMax * (kFeedOutMax - feedOutFlame)), kFillModeSolid);
	Novice::DrawBox(0, 0, BaseConst::kWindowWidth, BaseConst::kWindowHeight, 0.0f, 0xFFFFFF00 + (255 / kFeedInMax * feedInFlame), kFillModeSolid);

}


// bgm�n���h��
int GameClear::bgmHandle = -1;