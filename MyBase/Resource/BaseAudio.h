﻿#pragma once
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

#pragma region ボス

	// 開く音
	static int kBossOpen;

	// 閉じる音
	static int kBossClose;

	// 突進する音
	static int kBossRush;

	// ブレード展開音
	static int kBossDeployBlade;
	// ブレード斬撃音
	static int kBossSlash;

	// 銃を取り出す音
	static int kBossPickGun;
	// 射撃音
	static int kBossShot;
	
	// ダメージ音
	static int kBossDamage;

#pragma endregion

#pragma region Player

	// ジャンプ
	static int kPlayerJump;
	// 被ダメージ
	static int kPlayerDamage;
	// 射撃
	static int kPlayerShoot;
	// 排莢
	static int kPlayerEjection;

#pragma endregion


#pragma region Wire

	// ワイヤーがヒット
	static int kWireHit;
	// ワイヤーが切れる
	static int kWireCut;

#pragma endregion

};