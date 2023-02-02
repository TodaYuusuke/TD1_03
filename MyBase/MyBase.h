#pragma once
#include "MyBase/Define/BaseEnum.h"
#include "MyBase/Define/BaseStruct.h"

#include "MyBase/Effect/BaseEffectManager.h"

#include "MyBase/Resource/BaseTexture.h"
#include "MyBase/Resource/BaseAudio.h"
#include "MyBase/Resource/BaseConst.h"

#include "MyBase/Other/BaseDraw.h"
#include "MyBase/Other/BaseInput.h"
#include "MyBase/Other/BaseMath.h"

#include <Novice.h>
#include <stdlib.h>
#include <time.h>
#include <memory>

#include "Class/PublicFlag/PublicFlag.h"

////////////////////////////////////
/* - Baseクラス全てを管理するクラス - */
////////////////////////////////////


class MyBase
{

private: // メンバ関数

	// コンストラクタ（非公開）
	MyBase();
	// デストラクタ（非公開）
	~MyBase();

public: // メンバ関数

	// 初期化
	static void Initialize();
	// 更新
	static void Update();
	// 描画
	static void Draw();

private: // メンバ変数

	// 演出用変数
	static float easingT;
	static float width;

	// 演出スキップ用変数
	static int longPressedFrame;

};