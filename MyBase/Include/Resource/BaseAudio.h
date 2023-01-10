#pragma once
#include <Novice.h>


///////////////////////////////////////////////////////
/* - ゲーム内で使う全てのオーディオファイルを管理するクラス - */
///////////////////////////////////////////////////////


class BaseAudio
{

public: // メンバ関数

	// 初期化
	static void Initialize();

	// BGMとSEのvolumeを初期設定に戻す
	static void InitializeVolume();


	// ロード関数
	// 返り値：ロードが完了した場合はtrue
	// 引数：無し
	// オーディオのロードを100分割で行う。全てのロードが完了するまで呼び出させる（今回は％は実装しない、ロードするだけ）
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


public: // 静的なオーディオの変数

	// BGM系の音量
	static float BGMvolume;
	// SE系の音量
	static float SEvolume;

};