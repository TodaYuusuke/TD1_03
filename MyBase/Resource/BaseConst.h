#pragma once
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

	// マップの大きさ
	const static int kMapSizeWidth = 75;
	const static int kMapSizeHeight = 35;

	// マップチップのサイズ
	static int kMapChipSizeWidth;
	static int kMapChipSizeHeight;

	// マップデータ
	static int kMapData[kMapSizeHeight][kMapSizeWidth];

#pragma endregion

};