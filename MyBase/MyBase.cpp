#include "MyBase/MyBase.h"


// 初期化
void MyBase::Initialize() {

	// テクスチャの初期化
	BaseTexture::Initialize();
	// テクスチャのロード（本来の使い方とは違うが、今回はこれでいい）
	BaseTexture::Loading();
	// オーディオの初期化
	BaseAudio::Initialize();
	BaseAudio::InitializeVolume();
	// オーディオのロード（本来の使い方とは違うが、今回はこれでいい）
	BaseAudio::Loading();
	// 定数の初期化
	BaseConst::Initialize();
	// 定数のロード（本来の使い方とは違うが、今回はこれでいい）
	BaseConst::Loading();


	// インプットの初期化
	BaseInput::Initialize();
	// エフェクトマネージャーの初期化
	BaseEffectManager::Initialize();

	// スクリーン座標を初期化
	BaseDraw::SetScreenPosition({ 0,1080 });

	// 演出用変数
	easingT = 0;
	width = 0;

	// 乱数の初期化
	srand(time(nullptr));
}

// 更新
void MyBase::Update() {
	BaseInput::Update();

	// デバッグ用
	// 定数のホットリロード
	if (BaseInput::GetKeyboardState(DIK_F1, Trigger)) {
		BaseConst::Loading();
	}
	if (BaseInput::GetKeyboardState(DIK_RALT, Press) && BaseInput::GetKeyboardState(DIK_RETURN, Trigger)) {
		// フルスクリーンモード切り替え
		BaseDraw::ChangeFullScreen();
	}

	BaseEffectManager::Update();

}

// 描画
void MyBase::Draw(){
	BaseEffectManager::Draw();
	BaseInput::Draw();

	// 演出が始まったら黒幕を表示
	if (PublicFlag::kisStaging) {
		easingT += 1.0f / 60.0f;
		if (easingT > 0.5f) {
			easingT = 0.5f;
		}
		width = BaseDraw::Ease_Out(easingT, 0, BaseConst::kWindowWidth, 0.5f);
	}
	else {
		easingT -= 1.0f / 60.0f;
		if (easingT < 0) {
			easingT = 0;
		}
		width = BaseDraw::Ease_In(easingT, 0, BaseConst::kWindowWidth, 0.5f);
	}


	Novice::DrawBox(0, 0, width, 100, 0, BLACK, kFillModeSolid);
	Novice::DrawBox(BaseConst::kWindowWidth - width, BaseConst::kWindowHeight - 100, width, 100, 0, BLACK, kFillModeSolid);
}


// 演出用変数
float MyBase::easingT;
float MyBase::width;