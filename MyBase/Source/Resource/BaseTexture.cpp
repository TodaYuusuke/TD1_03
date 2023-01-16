#include "MyBase/Include/Resource/BaseTexture.h"

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

#pragma endregion
