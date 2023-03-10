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

#pragma region 背景

	// 背景フレーム
	static int kBackGroundFrame;
	
	/// 背景
	// 都市
	static int kBackGroundCity;
	// 森
	static int kBackGroundForest;

#pragma endregion


#pragma region マップ

	// マップチップサンプル
	// 0 ... 枠なし
	// 1,2,3,4 ... 上,右,下,左
	// 5,6,7,8 ... 右上,右下,左下,左上
	// 9,10,11,12 ... 下以外,左以外,上以外,右以外
	// 13 ... 全部
	static const int kTextureMapChipSize = 14;
	static int kTextureMapChip[kTextureMapChipSize];

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
	static int kBossLHook;
	static int kBossRHook;

	// 武器
	static int kBossBlade;
	static int kBossGun;

	// ボスの発射する弾
	static int kBossBullet;

#pragma endregion

#pragma region UI

	// A ボタン
	static int kUserInterfaceA[2];
	// Space
	static int kUserInterfaceSpace[2];
	// Skip
	static int kUserInterfaceSkip[2];

#pragma endregion

#pragma region プレイヤー

	// ハート
	static int kPlayerHeart[2];

	// 左
	// アイドル
	static int kLPlayerIdle;
	// 走る
	static int kLPlayerRun[2];
	// ジャンプ
	static int kLPlayerJump[4];
	// ワイヤ射出
	static int kLPlayerShot;
	// ワイヤ引き寄せ
	static int kLPlayerPull;

	// 右
	// アイドル
	static int kRPlayerIdle;
	// 走る
	static int kRPlayerRun[2];
	// ジャンプ
	static int kRPlayerJump[4];
	// ワイヤ射出
	static int kRPlayerShot;
	// ワイヤ引き寄せ
	static int kRPlayerPull;

#pragma endregion

#pragma region その他

	// ブロック
	static int kBlockTexture;
	// ブロックの破片
	const static int kBlockScrapAmount = 12;
	static int kBlockScrap[12];

#pragma endregion
};