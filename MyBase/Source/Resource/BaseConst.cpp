#include "MyBase/Include/Resource/BaseConst.h"

// 初期化
void BaseConst::Initialize() {
	LoadingPercent = 0;
	isLoadingComplete = false;
}


// ロード関数
// 返り値：ロードが完了した場合はtrue
// 引数：無し
// 定数のロードを100分割で行う。全てのロードが完了するまで呼び出させる（今回は％は実装しない、ロードするだけ）
bool BaseConst::Loading() {


	return true;
}


// ロード率を取得する関数
// 返り値：現在のロード率（％）
// 引数：無し
// 現在のロード状況を取得する関数。
int BaseConst::GetLoadingPercent() {
	return LoadingPercent;
}


//////////////////////////////////
/* - staticメンバ変数の実態を宣言 - */
//////////////////////////////////

int BaseConst::LoadingPercent;
bool BaseConst::isLoadingComplete;


#pragma region 解像度

// ウィンドウ解像度（横方向）
int BaseConst::kWindowWidth = 1920;
// ウィンドウ解像度（縦方向）
int BaseConst::kWindowHeight = 1080;

#pragma endregion


#pragma region プレイヤー

// プレイヤーのサイズ
Point BaseConst::kPlayerSize = { 64,128 };

// プレイヤーの移動値
Point BaseConst::kPlayerSpeed = { 4.0f,40.0f };

#pragma endregion

#pragma region ワイヤー

// ワイヤーの弾速
float BaseConst::kWireSpeed = 40;

// ワイヤーの最大の長さ
float BaseConst::kWireMaxLength = 100.0f;
// ワイヤーの最大存在数
//int BaseConst::kWireMaxAmount = 3;

#pragma endregion