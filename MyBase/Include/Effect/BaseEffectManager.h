#pragma once
#include "Base/Include/Define/BaseEnum.h"
#include "Base/Include/Define/BaseStruct.h"

#include "Base/Include/Effect/BaseEffect.h"


class BaseEffectManager
{
public: // メンバ関数

	// 初期化
	static void Initialize();
	// 更新
	static void Update();
	// 描画
	static void Draw();


	// 新規エフェクト登録関数
	// 返り値：エフェクトがセットされた番号
	// 引数：
	// position ... 中心のワールド座標
	// effectType ... エフェクトの種類
	static int MakeNewEffect(Point position, EffectType effectType);

	// エフェクトを終了させる関数
	// 返り値：なし
	// 引数：
	// effectNum ... エフェクト番号
	static void EndEffect(int effectNum);

	// エフェクトが終了したかを調べる関数
	// 返り値：エフェクトが終了済み ... true 、 そうでない場合 ... false
	// 引数：
	// effectNum ... エフェクト番号
	static bool isEndEffect(int effectNum);


private: // メンバ変数

	// エフェクト配列のサイズ
	const static int effectArraySize = 1024;

	// エフェクトの配列
	static BaseEffect* effects[effectArraySize];

	// 次に追加するエフェクトの添字
	static int nextIndex;
};

