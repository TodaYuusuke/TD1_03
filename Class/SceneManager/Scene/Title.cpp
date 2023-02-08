#include "Class/SceneManager/Scene/Title.h"

// コンストラクタ
Title::Title() {
	Initialize();
}
// デストラクタ
Title::~Title() {

}



// 初期化
void Title::Initialize() {

	nextScene = sceneNone;

	PublicFlag::Initialize();
	BaseDraw::SetScreenPosition({ 0,1080 });

	reticlePosition = { 1000,800 };
	preMousePosition = BaseInput::GetMousePosition();
	isToPlay = false;
	isToEnd = false;

	isSelected = false;

	feedInFlame = kFeedInMax;
	feedOutFlame = kFeedOutMax;

	// BGM再生
	if (Novice::IsPlayingAudio(bgmHandle) == 0 || bgmHandle == -1) {
		bgmHandle = Novice::PlayAudio(BaseAudio::kBGMTitle, true, 0.1f);
	}
}
// 更新
void Title::Update() {
	if (0 < feedInFlame) {
		feedInFlame--;
	}

	// ワールド座標に戻さず計算
	Point rightStick;
	BaseInput::GetControllerRightJoysState(&rightStick);
	int x, y;
	Novice::GetMousePosition(&x, &y);
	// マウスが動いている時
	if (preMousePosition.x != x || preMousePosition.y != y) {
		reticlePosition = BaseInput::GetMousePosition();
	}
	// スティックが入力されている時
	if (BaseMath::GetLength(rightStick) != 0.0f) {
		reticlePosition.x += 20 * rightStick.x;
		reticlePosition.y += 20 * rightStick.y;
	}
	// 照準を画面内に収める
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
		// 「スタート」の中にマウスがある場合
		if (BaseConst::kTitletoPlayLeftTop.x < reticlePosition.x && reticlePosition.x < BaseConst::kTitletoPlayRightBottom.x &&
			BaseConst::kTitletoPlayLeftTop.y < reticlePosition.y && reticlePosition.y < BaseConst::kTitletoPlayRightBottom.y) {
			if (!Novice::IsPlayingAudio(BaseAudio::kSelect) && !isToPlay) {
				Novice::PlayAudio(BaseAudio::kSelect, 0, BaseAudio::SEvolume);
			}
			isToPlay = true;
			if (BaseInput::GetMouseState(LeftClick, Trigger) ||
				BaseInput::GetControllerState(kControllerButtonL2A, Trigger) ||
				BaseInput::GetControllerState(kControllerButtonR2B, Trigger)) {
				isSelected = true;
				feedOutFlame = kFeedOutMax;
				Novice::PlayAudio(BaseAudio::kSpecialDecide, 0, BaseAudio::SEvolume);
			}
		}
		else {
			isToPlay = false;
		}
		if (BaseConst::kTitletoEndLeftTop.x < reticlePosition.x && reticlePosition.x < BaseConst::kTitletoEndRightBottom.x &&
			BaseConst::kTitletoEndLeftTop.y < reticlePosition.y && reticlePosition.y < BaseConst::kTitletoEndRightBottom.y) {
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
			
			if (isToPlay) {
				nextScene = sceneTutorialStage;
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
// 描画
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



	BaseDraw::DrawSprite({ 100,200 - 64 * 3 }, BaseTexture::kBlockTexture, { 1,1 }, 0.0f, WHITE);
	BaseDraw::DrawSprite({ 100,200 - 64 * 2 }, BaseTexture::kBlockTexture, { 1,1 }, 0.0f, WHITE);
	BaseDraw::DrawSprite({ 100,200 - 64 }, BaseTexture::kBlockTexture, { 1,1 }, 0.0f, WHITE);
	BaseDraw::DrawSprite({ 100,200 }, BaseTexture::kBlockTexture, { 1,1 }, 0.0f, WHITE);
	BaseDraw::DrawSprite({ 100,300 }, BaseTexture::kRPlayerIdle, { 1,1 }, 0.0f, WHITE);

	// 照準
	if (isToPlay || isToEnd) {
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


// bgmハンドル
int Title::bgmHandle = -1;