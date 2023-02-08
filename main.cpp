#include <Novice.h>
#include "MyBase/MyBase.h"

#include "Class/SceneManager/SceneManager.h"

const char kWindowTitle[] = "チーム開発";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, BaseConst::kWindowWidth, BaseConst::kWindowHeight);

	MyBase::Initialize();

	// カーソルの非表示
	Novice::SetMouseCursorVisibility(false);
	// デフォルトでフルスクリーン
	//BaseDraw::ChangeFullScreen();
	// スクリーン座標をset
	BaseDraw::SetScreenPosition({ 0,1080 });

	SceneManager scene;
	scene.Initialize();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		///
		/// ↓更新処理ここから
		///

		// MyBaseをアップデート
		MyBase::Update();
		// シーン更新
		scene.Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// シーン描画
		scene.Draw();
		// MyBaseを描画
		MyBase::Draw();

		///
		/// ↑描画処理ここまで
		///

		// プログラム終了
		if (BaseInput::GetKeyboardState(DIK_ESCAPE, Trigger)) {
			break;
		}
		
		// フレームの終了
		Novice::EndFrame();
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
