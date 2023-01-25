#pragma once
#include <Novice.h>


///////////////////////////////////////////////////////
/* - ゲーム内で使う全てのテクスチャファイルを管理するクラス - */
///////////////////////////////////////////////////////


class BaseTexture
{

public: // メンバ関数

	// 初期化
	static void Initialize();


	// ロード関数
	// 返り値：ロードが完了した場合はtrue
	// 引数：無し
	// テクスチャのロードを100分割で行う。全てのロードが完了するまで呼び出させる（今回は％は実装しない、ロードするだけ）
	static bool Loading();

	// ロード率を取得する関数
	// 返り値：現在のロード率（％）
	// 引数：無し
	// 現在のロード状況を取得する関数。
	static int GetLoadingPercent();


private: // メンバ変数

	// 現在のロード率
	static int LoadingPercent;
	// ロードが完了したか
	static bool isLoadingComplete;


public: // 静的なテクスチャの変数

	// デバッグ用テクスチャ
	static int kDebugTexture;

#pragma region マップ

	// マップチップサンプル
	// 0 ... 枠なし
	// 1,2,3,4 ... 上,右,下,左
	// 5,6,7,8 ... 右上,右下,左下,左上
	// 9,10,11,12 ... 下以外,左以外,上以外,右以外
	// 13 ... 全部
	static int kTextureMapChipSample[];
	static const int kTextureMapChipSampleSize = 14;

	// 抜けられる床
	static int kTextureMapChipFloor;

#pragma endregion

#pragma region ボス

	// ボスの核
	static int kBossCore;

	// ボスのカバー
	static int kBossRCover;
	static int kBossLCover;

	// フック
	static int kBossHook;

#pragma endregion

#pragma region その他

	// ブロック
	static int kBlockTexture;

#pragma endregion
};