#include "MyBase/Resource/BaseTexture.h"

// 初期化
void BaseTexture::Initialize() {
	LoadingPercent = 0;
	isLoadingComplete = false;
}


// ロード関数
// 返り値：ロードが完了した場合はtrue
// 引数：無し
// テクスチャのロードを100分割で行う。全てのロードが完了するまで呼び出させる（今回は％は実装しない、ロードするだけ）
bool BaseTexture::Loading() {

	kDebugTexture = Novice::LoadTexture("white1x1.png");

#pragma region マップ

	// マップチップサンプル
	kTextureMapChipSample[0] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample1.png");
	kTextureMapChipSample[1] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample2.png");
	kTextureMapChipSample[2] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample3.png");
	kTextureMapChipSample[3] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample4.png");
	kTextureMapChipSample[4] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample5.png");
	kTextureMapChipSample[5] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample6.png");
	kTextureMapChipSample[6] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample7.png");
	kTextureMapChipSample[7] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample8.png");
	kTextureMapChipSample[8] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample9.png");
	kTextureMapChipSample[9] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample10.png");
	kTextureMapChipSample[10] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample11.png");
	kTextureMapChipSample[11] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample12.png");
	kTextureMapChipSample[12] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample13.png");
	kTextureMapChipSample[13] = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Sample14.png");

	// 抜けられる床
	kTextureMapChipFloor = Novice::LoadTexture("./Resources/Texture/MapChip/MapChip_Floor.png");

#pragma endregion

#pragma region ボス

	// ボスの核
	kBossCore = Novice::LoadTexture("./Resources/Texture/Boss/Kernel.png");

	// ボスのカバー
	kBossRCover = Novice::LoadTexture("./Resources/Texture/Boss/RCover.png");
	kBossLCover = Novice::LoadTexture("./Resources/Texture/Boss/LCover.png");

	// ボスのフック
	kBossLHook = Novice::LoadTexture("./Resources/Texture/Boss/LHook.png");
	kBossRHook = Novice::LoadTexture("./Resources/Texture/Boss/RHook.png");
#pragma endregion

#pragma region UI

	kUserInterfaceA[0] = Novice::LoadTexture("./Resources/Texture/UI/A0.png");
	kUserInterfaceA[1] = Novice::LoadTexture("./Resources/Texture/UI/A1.png");
	
	kUserInterfaceSpace[0] = Novice::LoadTexture("./Resources/Texture/UI/Space0.png");
	kUserInterfaceSpace[1] = Novice::LoadTexture("./Resources/Texture/UI/Space1.png");
	
	kUserInterfaceSkip[0] = Novice::LoadTexture("./Resources/Texture/UI/Skip0.png");
	kUserInterfaceSkip[1] = Novice::LoadTexture("./Resources/Texture/UI/Skip1.png");

#pragma endregion

#pragma region プレイヤー

	// ハート
	kPlayerHeart[0] = Novice::LoadTexture("./Resources/Texture/Player/HeartFull.png");
	kPlayerHeart[1] = Novice::LoadTexture("./Resources/Texture/Player/HeartHalf.png");

	// 左
	// アイドル
	kLPlayerIdle = Novice::LoadTexture("./Resources/Texture/Player/Left/L_chara_idle.png");
	// 走る
	kLPlayerRun[0] = Novice::LoadTexture("./Resources/Texture/Player/Left/L_chara_dash0.png");
	kLPlayerRun[1] = Novice::LoadTexture("./Resources/Texture/Player/Left/L_chara_dash1.png");
	// ジャンプ
	kLPlayerJump[0] = Novice::LoadTexture("./Resources/Texture/Player/Left/L_chara_jump0.png");
	kLPlayerJump[1] = Novice::LoadTexture("./Resources/Texture/Player/Left/L_chara_jump1.png");
	kLPlayerJump[2] = Novice::LoadTexture("./Resources/Texture/Player/Left/L_chara_jump2.png");
	kLPlayerJump[3] = Novice::LoadTexture("./Resources/Texture/Player/Left/L_chara_jump3.png");
	// ワイヤ射出
	kLPlayerShot = Novice::LoadTexture("./Resources/Texture/Player/Left/L_chara_shot.png");
	// ワイヤ引き寄せ
	kLPlayerPull = Novice::LoadTexture("./Resources/Texture/Player/Left/L_chara_pull.png");

	// 右
	// アイドル
	kRPlayerIdle = Novice::LoadTexture("./Resources/Texture/Player/Right/R_chara_idle.png");
	// 走る
	kRPlayerRun[0] = Novice::LoadTexture("./Resources/Texture/Player/Right/R_chara_dash0.png");
	kRPlayerRun[1] = Novice::LoadTexture("./Resources/Texture/Player/Right/R_chara_dash1.png");
	// ジャンプ
	kRPlayerJump[0] = Novice::LoadTexture("./Resources/Texture/Player/Right/R_chara_jump0.png");
	kRPlayerJump[1] = Novice::LoadTexture("./Resources/Texture/Player/Right/R_chara_jump1.png");
	kRPlayerJump[2] = Novice::LoadTexture("./Resources/Texture/Player/Right/R_chara_jump2.png");
	kRPlayerJump[3] = Novice::LoadTexture("./Resources/Texture/Player/Right/R_chara_jump3.png");
	// ワイヤ射出
	kRPlayerShot = Novice::LoadTexture("./Resources/Texture/Player/Right/R_chara_shot.png");
	// ワイヤ引き寄せ
	kRPlayerPull = Novice::LoadTexture("./Resources/Texture/Player/Right/R_chara_pull.png");

#pragma endregion

#pragma region その他

	// ブロック
	kBlockTexture = Novice::LoadTexture("./Resources/Texture/Block/Block.png");
	// ブロックの破片
	kBlockScrap[0] = Novice::LoadTexture("./Resources/Texture/Block/Scrap0.png");
	kBlockScrap[1] = Novice::LoadTexture("./Resources/Texture/Block/Scrap1.png");
	kBlockScrap[2] = Novice::LoadTexture("./Resources/Texture/Block/Scrap2.png");
	kBlockScrap[3] = Novice::LoadTexture("./Resources/Texture/Block/Scrap3.png");
	kBlockScrap[4] = Novice::LoadTexture("./Resources/Texture/Block/Scrap4.png");
	kBlockScrap[5] = Novice::LoadTexture("./Resources/Texture/Block/Scrap5.png");
	kBlockScrap[6] = Novice::LoadTexture("./Resources/Texture/Block/Scrap6.png");
	kBlockScrap[7] = Novice::LoadTexture("./Resources/Texture/Block/Scrap7.png");
	kBlockScrap[8] = Novice::LoadTexture("./Resources/Texture/Block/Scrap8.png");
	kBlockScrap[9] = Novice::LoadTexture("./Resources/Texture/Block/Scrap9.png");
	kBlockScrap[10] = Novice::LoadTexture("./Resources/Texture/Block/Scrap10.png");
	kBlockScrap[11] = Novice::LoadTexture("./Resources/Texture/Block/Scrap11.png");

#pragma endregion

	return true;
}


// ロード率を取得する関数
// 返り値：現在のロード率（％）
// 引数：無し
// 現在のロード状況を取得する関数。
int BaseTexture::GetLoadingPercent() {
	return LoadingPercent;
}


//////////////////////////////////
/* - staticメンバ変数の実態を宣言 - */
//////////////////////////////////

int BaseTexture::LoadingPercent;
bool BaseTexture::isLoadingComplete;


int BaseTexture::kDebugTexture;

#pragma region マップ

int BaseTexture::kTextureMapChipSample[kTextureMapChipSampleSize];

// 抜けられる床
int BaseTexture::kTextureMapChipFloor;

#pragma endregion


#pragma region ボス

// ボスの核
int BaseTexture::kBossCore;

// ボスのカバー
int BaseTexture::kBossRCover;
int BaseTexture::kBossLCover;

int BaseTexture::kBossLHook;
int BaseTexture::kBossRHook;

#pragma endregion

#pragma region UI

int BaseTexture::kUserInterfaceA[2];
int BaseTexture::kUserInterfaceSpace[2];
int BaseTexture::kUserInterfaceSkip[2];

#pragma endregion

#pragma region プレイヤー

// ハート
int BaseTexture::kPlayerHeart[2];

// 左
// アイドル
int BaseTexture::kLPlayerIdle;
// 走る
int BaseTexture::kLPlayerRun[2];
// ジャンプ
int BaseTexture::kLPlayerJump[4];
// ワイヤ射出
int BaseTexture::kLPlayerShot;
// ワイヤ引き寄せ
int BaseTexture::kLPlayerPull;

// 右
// アイドル
int BaseTexture::kRPlayerIdle;
// 走る
int BaseTexture::kRPlayerRun[2];
// ジャンプ
int BaseTexture::kRPlayerJump[4];
// ワイヤ射出
int BaseTexture::kRPlayerShot;
// ワイヤ引き寄せ
int BaseTexture::kRPlayerPull;

#pragma endregion

#pragma region その他

// ブロック
int BaseTexture::kBlockTexture;
// ブロックの破片
int BaseTexture::kBlockScrap[kBlockScrapAmount];

#pragma endregion