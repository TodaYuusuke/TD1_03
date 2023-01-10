#pragma once
#include "Base/Include/Define/BaseEnum.h"
#include "Base/Include/Define/BaseStruct.h"

#include "Base/Include/Effect/BaseEffectManager.h"

#include "Base/Include/Resource/BaseTexture.h"
#include "Base/Include/Resource/BaseAudio.h"
#include "Base/Include/Resource/BaseConst.h"

#include "Base/Include/Other/BaseDraw.h"
#include "Base/Include/Other/BaseInput.h"
#include "Base/Include/Other/BaseMath.h"

#include <Novice.h>
#include <time.h>
#include <memory>

////////////////////////////////////
/* - Baseクラス全てを管理するクラス - */
////////////////////////////////////


class Base
{

private: // メンバ関数

	// コンストラクタ（非公開）
	Base();
	// デストラクタ（非公開）
	~Base();

public: // メンバ関数

	// 初期化
	static void Initialize();
	// 更新
	static void Update();
	// 描画
	static void Draw();

};