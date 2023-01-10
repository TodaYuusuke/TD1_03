#include "MyBase/Include/Resource/BaseAudio.h"

// 初期化
void BaseAudio::Initialize() {
	LoadingPercent = 0;
	isLoadingComplete = false;

	InitializeVolume();
}


// BGMとSEのvolumeを初期設定に戻す
void BaseAudio::InitializeVolume() {
	BGMvolume = 0.3f;
	SEvolume = 0.5f;
}


// ロード関数
// 返り値：ロードが完了した場合はtrue
// 引数：無し
// オーディオのロードを100分割で行う。全てのロードが完了するまで呼び出させる（今回は％は実装しない、ロードするだけ）
bool BaseAudio::Loading() {


	return true;
}


// ロード率を取得する関数
// 返り値：現在のロード率（％）
// 引数：無し
// 現在のロード状況を取得する関数。
int BaseAudio::GetLoadingPercent() {
	return LoadingPercent;
}


//////////////////////////////////
/* - staticメンバ変数の実態を宣言 - */
//////////////////////////////////

// 現在のロード率
int BaseAudio::LoadingPercent;
// ロードが完了したか
bool BaseAudio::isLoadingComplete;
// BGM系の音量
float BaseAudio::BGMvolume;
// SE系の音量
float BaseAudio::SEvolume;

