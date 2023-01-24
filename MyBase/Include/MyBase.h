#pragma once
#include "MyBase/Include/Define/BaseEnum.h"
#include "MyBase/Include/Define/BaseStruct.h"

#include "MyBase/Include/Effect/BaseEffectManager.h"

#include "MyBase/Include/Resource/BaseTexture.h"
#include "MyBase/Include/Resource/BaseAudio.h"
#include "MyBase/Include/Resource/BaseConst.h"

#include "MyBase/Include/Other/BaseDraw.h"
#include "MyBase/Include/Other/BaseInput.h"
#include "MyBase/Include/Other/BaseMath.h"

#include <Novice.h>
#include <stdlib.h>
#include <time.h>
#include <memory>

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

};