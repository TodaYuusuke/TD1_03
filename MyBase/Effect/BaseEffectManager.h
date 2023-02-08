#pragma once
#include "MyBase/Define/BaseEnum.h"
#include "MyBase/Define/BaseStruct.h"

#include "MyBase/Effect/BaseEffect.h"

#include "MyBase/Effect/Inheritance/BlockBreak.h"
#include "MyBase/Effect/Inheritance/ConcreteDust.h"
#include "MyBase/Effect/Inheritance/BalloonDead.h"


class BaseEffectManager
{
public: // メンバ関数

	// 初期化
	static void Initialize();
	// 更新
	static void Update();
	// 描画
	static void Draw();


	// 空いているエフェクトの枠を受け取る関数
	static void GetEmptyID();

	// 新規エフェクト登録関数
	// 返り値：エフェクトがセットされた番号
	// 引数：それぞれ
	static int MakeNewEffectBlockBreak(Point);
	static int MakeNewEffectConcreteDust(Point);
	static int MakeNewEffectBalloonDead(Point, bool);


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
	const static int effectArraySize = 128;

	// エフェクトの配列
	static BaseEffect* effects[effectArraySize];

	// 次に追加するエフェクトの添字
	static int nextIndex;
};

