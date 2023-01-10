#pragma once
#include "Base/Include/Define/BaseStruct.h"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>

using namespace std;

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
	static vector<string> split(string& input, char delimiter)
	{
		istringstream stream(input);
		string field;
		vector<string> result;
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
};