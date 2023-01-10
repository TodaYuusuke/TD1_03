#include "Base/Include/Base.h"


// 初期化
void Base::Initialize() {

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


	// 乱数の初期化
	srand(time(nullptr));
}

// 更新
void Base::Update() {
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
void Base::Draw(){
	BaseEffectManager::Draw();
	BaseInput::Draw();
}