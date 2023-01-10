#include <Novice.h>
#include "MyBase/Include/MyBase.h"

#include "Debug.h"

const char kWindowTitle[] = "チーム開発";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, BaseConst::kWindowWidth, BaseConst::kWindowHeight);

	BaseDraw::SetScreenPosition({ 0,1080 });

	// デバッグクラス
	Debug debug;
	// デバッグ初期化
	debug.Initialize();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		///
		/// ↓更新処理ここから
		///

		// デバッグ更新
		debug.Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// デバッグ描画
		debug.Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
