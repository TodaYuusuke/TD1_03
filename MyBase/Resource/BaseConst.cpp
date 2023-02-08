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
	//std::vector<std::string> map;
	std::ifstream tutorialMapifs("./Resources/Const/TutorialStage.csv");
	std::string line;

	int y = 0;
	while (getline(tutorialMapifs, line)) {

		std::vector<std::string> strvec = split(line, ',');

		for (int x = 0; x < strvec.size(); x++) {
			kTutorialStageData[y][x] = stoi(strvec.at(x));
		}

		y++;
	}

	// ボスステージロード
	std::ifstream bossMapifs("./Resources/Const/BossStage.csv");

	y = 0;

	while (getline(bossMapifs, line)) {

		std::vector<std::string> strvec = split(line, ',');

		for (int x = 0; x < strvec.size(); x++) {
			kBossStageData[y][x] = stoi(strvec.at(x));
		}

		y++;
	}

	// プレイヤーのアニメーション毎の描画フレームを設定
	kPlayerAnimationFlame[PlayerState::playerIdle] = 1;
	kPlayerAnimationFlame[PlayerState::playerRun] = 3;
	kPlayerAnimationFlame[PlayerState::playerJump] = 2;
	kPlayerAnimationFlame[PlayerState::playerRase] = 1;
	kPlayerAnimationFlame[PlayerState::playerFall] = 1;
	kPlayerAnimationFlame[PlayerState::playerLand] = 2;
	kPlayerAnimationFlame[PlayerState::playerShot] = 10;
	kPlayerAnimationFlame[PlayerState::playerPull] = 10;


	// チュートリアルステージの進行度の目安
	kRespawnProgress[0].x = 112 * BaseConst::kMapChipSizeWidth;	// 初ワイヤー
	kRespawnProgress[0].y = 3 * BaseConst::kMapChipSizeHeight + 50;
	kRespawnProgress[1].x = 206 * BaseConst::kMapChipSizeWidth;	// 初雑魚敵
	kRespawnProgress[1].y = 3 * BaseConst::kMapChipSizeHeight + 50;
	kRespawnProgress[2].x = 383 * BaseConst::kMapChipSizeWidth;	// 中ボス前
	kRespawnProgress[2].y = 29 * BaseConst::kMapChipSizeHeight + 50;
	kRespawnProgress[3].x = 458 * BaseConst::kMapChipSizeWidth;	// 雑魚ラッシュ前
	kRespawnProgress[3].y = 3 * BaseConst::kMapChipSizeHeight + 50;
	
	kGimmickProgress[0] = 25 * BaseConst::kMapChipSizeWidth;	// ジャンプチュートリアル
	kGimmickProgress[1] = 123 * BaseConst::kMapChipSizeWidth;	// ワイヤーチュートリアル
	kGimmickProgress[2] = 216 * BaseConst::kMapChipSizeWidth;	// 雑魚召喚、チュートリアル
	kGimmickProgress[3] = 290 * BaseConst::kMapChipSizeWidth;	// 箱が降ってくる
	kGimmickProgress[4] = 308 * BaseConst::kMapChipSizeWidth;	// 雑魚召喚
	kGimmickProgress[5] = 388 * BaseConst::kMapChipSizeWidth;	// 中ボス召喚
	kGimmickProgress[6] = 473 * BaseConst::kMapChipSizeWidth;	// 雑魚ラッシュ開始


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
Point BaseConst::kPlayerSize = { 60,100 };

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

// 走るアニメーション 2
int BaseConst::kPlayerTextureRunNum = 2;

// ジャンプアニメーション 4
int BaseConst::kPlayerTextureJumpNum = 4;

// アニメーション固定経過フレーム
int BaseConst::kPlayerMaxAnimationFlame = 8;

// アニメーション毎の描画フレーム
int BaseConst::kPlayerAnimationFlame[PlayerState::kPlayerStateCount];

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

// マップデータ
int BaseConst::kTutorialStageData[kTutorialStageSizeHeight][kTutorialStageSizeWidth];
int BaseConst::kBossStageData[kBossStageSizeHeight][kBossStageSizeWidth];

// チュートリアルステージの進行度の目安
Point BaseConst::kRespawnProgress[4];
int BaseConst::kGimmickProgress[7];

#pragma endregion

#pragma region Scene

// あらかじめ描画する完成度
float BaseConst::kGameOverFirstValue = 0.2f;
float BaseConst::kGameOverFlame = (1 - BaseConst::kGameOverFirstValue) / (float)BaseConst::kGameOverMaxFlame;

// 「タイトルへ戻る」各種座標
Point BaseConst::kGameOverTitleLeftTop = { 96,880 };
Point BaseConst::kGameOverTitleRightBottom = { 743,983 };

Point BaseConst::kGameOverRetryLeftTop = { 1210,880 };
Point BaseConst::kGameOverRetryRightBottom = { 1559,975 };

// 「スタート」各種座標
Point BaseConst::kTitletoPlayLeftTop = {1060,750};
Point BaseConst::kTitletoPlayRightBottom = { 1319,829 };
// 「エンド」各種座標
Point BaseConst::kTitletoEndLeftTop = { 1060,900 };
Point BaseConst::kTitletoEndRightBottom = {1249,978};

#pragma endregion