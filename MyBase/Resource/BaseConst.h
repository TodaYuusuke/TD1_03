#pragma once
#include "MyBase/Define/BaseEnum.h"
#include "MyBase/Define/BaseStruct.h"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>

///////////////////////////////////////////
/* - ゲーム内で共通で扱う定数を管理するクラス - */
///////////////////////////////////////////


class BaseConst
{

public: // メンバ関数

	// 初期化
	static void Initialize();


	// ロード関数
	// 返り値：ロードが完了した場合はtrue
	// 引数：無し
	// 定数のロードを100分割で行う。全てのロードが完了するまで呼び出させる（今回は％は実装しない、ロードするだけ）
	static bool Loading();

	// ロード率を取得する関数
	// 返り値：現在のロード率（％）
	// 引数：無し
	// 現在のロード状況を取得する関数。
	static int GetLoadingPercent();



	// string分割関数
	static std::vector<std::string> split(std::string& input, char delimiter)
	{
		std::istringstream stream(input);
		std::string field;
		std::vector<std::string> result;
		while (getline(stream, field, delimiter)) {
			result.push_back(field);
		}
		return result;
	}


private: // メンバ変数

	// 現在のロード率
	static int LoadingPercent;
	// ロードが完了したか
	static bool isLoadingComplete;


public: // 静的な定数

#pragma region 解像度

	// ウィンドウ解像度（横方向）
	static int kWindowWidth;
	// ウィンドウ解像度（縦方向）
	static int kWindowHeight;

#pragma endregion

#pragma region ブロック

	// ブロックが消えるまでのフレーム数
	static int kBlockVanishFlame;
	// ブロックが点滅し始めるフレーム
	static int kBlockBeVanish;

#pragma endregion

#pragma region プレイヤー

	// プレイヤーのサイズ
	static Point kPlayerSize;

	// 重力加速度
	static float kPlayerGravitationalAcceleration;
	// 全体の速度制限
	static float kPlayerVelocityLimit;

	// 移動 //

	// 平行移動の限界速度
	static float kPlayerWalkVelocityLimit;

	// ジャンプ //

	// ジャンプの速度
	static Point kPlayerJumpVelocity;
	// ジャンプのクールタイム
	static int kPlayerJumpCoolTime;

	// 照準 //

	// 照準の最大射程
	static int kPlayerReticleRange;

	// 照準の大きさ
	static int kPlayerReticleSize;

	// 走るアニメーション
	static int kPlayerTextureRunNum;

	// ジャンプアニメーション
	static int kPlayerTextureJumpNum;

	// アニメーション固定経過フレーム
	static int kPlayerMaxAnimationFlame;

	// アニメーション毎の描画フレーム
	static int kPlayerAnimationFlame[PlayerState::kPlayerStateCount];

#pragma endregion

#pragma region ワイヤー

	// ワイヤーの弾速
	static float kWireSpeed;

	// ワイヤーの最大の長さ
	static float kWireMaxLength;
	// ワイヤーの最大存在数
	const static int kWireMaxAmount = 5;

#pragma endregion

#pragma region マップ

	// マップチップのサイズ
	const static int kMapChipSizeWidth = 32;
	const static int kMapChipSizeHeight = 32;

	// チュートリアルステージの大きさ
	const static int kTutorialStageSizeWidth = 500;
	const static int kTutorialStageSizeHeight = 35;
	// ボスステージの大きさ
	const static int kBossStageSizeWidth = 75;
	const static int kBossStageSizeHeight = 35;


	// マップデータ
	static int kTutorialStageData[kTutorialStageSizeHeight][kTutorialStageSizeWidth];
	static int kBossStageData[kBossStageSizeHeight][kBossStageSizeWidth];

#pragma endregion

#pragma region GameOver

	// あらかじめ描画する完成度
	static float kGameOverFirstValue;
	// ゲームオーバー時の演出にかかるフレーム
	const static int kGameOverMaxFlame = 10;
	// ゲームオーバー演出に 1 フレーム単位での必要な時間
	static float kGameOverFlame;

	// 「タイトルへ戻る」各種座標
	static Point kGameOverTitleLeftTop;
	static Point kGameOverTitleRightBottom;
	// 「リトライ」各種座標
	static Point kGameOverRetryLeftTop;
	static Point kGameOverRetryRightBottom;

	// 余白
	const static int kGameOverPadding = 10;

#pragma endregion

#pragma region Effect

	// ワイヤーが刺さった時の粉
	// 粒子数
	const static int kConcreteDustNum = 20;


#pragma endregion


};