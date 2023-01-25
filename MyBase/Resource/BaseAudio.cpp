#include "MyBase/Resource/BaseAudio.h"

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

#pragma region ボス

	// ボスが開く音
	kBossOpen = Novice::LoadAudio("./Resources/Audio/Boss/kBossOpen.wav");

	// 閉じる音
	kBossClose = Novice::LoadAudio("./Resources/Audio/Boss/kBossClose.mp3");

	// 突進する音
	kBossRush = Novice::LoadAudio("./Resources/Audio/Boss/kBossRush.mp3");

	// 銃展開音
	kBossPickGun = Novice::LoadAudio("./Resources/Audio/Boss/kBossPickGun.wav");
	// 射撃音
	kBossShot = Novice::LoadAudio("./Resources/Audio/Boss/kBossShot.wav");

	// ブレード展開音
	kBossDeployBlade = Novice::LoadAudio("./Resources/Audio/Boss/kBossDeployBlade.wav");
	// 斬撃音
	kBossSlash = Novice::LoadAudio("./Resources/Audio/Boss/kBossSlash.wav");

#pragma endregion


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

#pragma region ボス

// 開く音
int BaseAudio::kBossOpen;

// 閉じる音
int BaseAudio::kBossClose;

// 突進する音
int BaseAudio::kBossRush;

// ブレード展開音
int BaseAudio::kBossDeployBlade;
// ブレード斬撃音
int BaseAudio::kBossSlash;

// 銃を取り出す音
int BaseAudio::kBossPickGun;
// 射撃音
int BaseAudio::kBossShot;


#pragma endregion
