#include "MyBase/Resource/BaseConst.h"

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

	// チュートリアルステージロード
	std::vector<std::string> map;
	std::ifstream mapifs("./Resources/Const/TutorialStage.csv");
	std::string line;

	int y = 0;

	while (getline(mapifs, line)) {

		std::vector<std::string> strvec = split(line, ',');

		for (int x = 0; x < strvec.size(); x++) {
			kTutorialStageData[y][x] = stoi(strvec.at(x));
		}

		y++;
	}

	// ボスステージロード
	mapifs.open("./Resources/Const/BossStage.csv");

	y = 0;

	while (getline(mapifs, line)) {

		std::vector<std::string> strvec = split(line, ',');

		for (int x = 0; x < strvec.size(); x++) {
			kBossStageData[y][x] = stoi(strvec.at(x));
		}

		y++;
	}

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

#pragma region ブロック

// ブロックが消えるまでのフレーム数
int BaseConst::kBlockVanishFlame = 1800;
// ブロックが点滅し始めるフレーム
int BaseConst::kBlockBeVanish = 300;


#pragma endregion

#pragma region プレイヤー

// プレイヤーのサイズ
Point BaseConst::kPlayerSize = { 64,128 };

// 重力加速度
float BaseConst::kPlayerGravitationalAcceleration = 9.8f / 30.0f;
// 全体の速度制限
float BaseConst::kPlayerVelocityLimit = 10.0f;

// 移動 //

// 平行移動の限界速度
float BaseConst::kPlayerWalkVelocityLimit = 3.0f;

// ジャンプ //

// ジャンプの速度
Point BaseConst::kPlayerJumpVelocity = { 0,9.8f };
// ジャンプのクールタイム
int BaseConst::kPlayerJumpCoolTime = 40;

// 照準 //

// 照準の最大射程
int BaseConst::kPlayerReticleRange = 1500;

// 照準のサイズ
int BaseConst::kPlayerReticleSize = 10;

#pragma endregion

#pragma region ワイヤー

// ワイヤーの弾速
float BaseConst::kWireSpeed = 40;

// ワイヤーの最大の長さ
float BaseConst::kWireMaxLength = 1500.0f;
// ワイヤーの最大存在数
//int BaseConst::kWireMaxAmount = 3;

#pragma endregion

#pragma region マップ

// マップチップのサイズ
int BaseConst::kMapChipSizeWidth = 32;
int BaseConst::kMapChipSizeHeight = 32;

// マップデータ
int BaseConst::kTutorialStageData[kTutorialStageSizeWidth][kTutorialStageSizeHeight];
int BaseConst::kBossStageData[kBossStageSizeHeight][kBossStageSizeWidth];

#pragma endregion
