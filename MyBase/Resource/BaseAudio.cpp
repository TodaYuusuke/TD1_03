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

	// 再起動音
	kBossReboot = Novice::LoadAudio("./Resources/Audio/Boss/kBossReboot.wav");

	// 振動音
	kBossVibration = Novice::LoadAudio("./Resources/Audio/Boss/kBossVib.wav");

	// ダメージ音
	kBossDamage = Novice::LoadAudio("./Resources/Audio/Boss/kBossDamage.mp3");

	// ボスが左右に引っ張られる音
	kBossPull = Novice::LoadAudio("./Resources/Audio/Boss/kBossPull.mp3");
	// ボスが弱点をさらす時の音
	kBossHardOpen = Novice::LoadAudio("./Resources/Audio/Boss/kBossHardOpen.mp3");

#pragma endregion

#pragma region Player

	// ジャンプ
	kPlayerJump = Novice::LoadAudio("./Resources/Audio/Player/Jump.mp3");
	// 被ダメージ
	kPlayerDamage = Novice::LoadAudio("./Resources/Audio/Player/Damage.mp3");
	// 射撃
	kPlayerShoot = Novice::LoadAudio("./Resources/Audio/Player/Shoot.mp3");
	// 排莢
	kPlayerEjection = Novice::LoadAudio("./Resources/Audio/Player/Ejection.mp3");

#pragma endregion

#pragma region Wire

	// ワイヤーがヒット
	kWireHit = Novice::LoadAudio("./Resources/Audio/Wire/Hit.mp3");
	// ワイヤーが切れる
	kWireCut = Novice::LoadAudio("./Resources/Audio/Wire/Cut.mp3");

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

// ボスの再起動音
int BaseAudio::kBossReboot;

// ボスの振動音
int BaseAudio::kBossVibration;

// ボスにダメージが入った時の音
int BaseAudio::kBossDamage;

// ボスが左右に引っ張られる音
int BaseAudio::kBossPull;
// ボスが弱点をさらす時の音
int BaseAudio::kBossHardOpen;

#pragma endregion

#pragma region Player

// ジャンプ
int BaseAudio::kPlayerJump;
// 被ダメージ
int BaseAudio::kPlayerDamage;
// 射撃
int BaseAudio::kPlayerShoot;
// 排莢
int BaseAudio::kPlayerEjection;

#pragma endregion

#pragma region Wire

// ワイヤーがヒット
int BaseAudio::kWireHit;
// ワイヤーが切れる
int BaseAudio::kWireCut;

#pragma endregion