#pragma once
#include "Base/Include/Define/BaseEnum.h"
#include "Base/Include/Define/BaseStruct.h"
#include "Base/Include/Resource/BaseConst.h"
#include "Base/Include/Resource/BaseTexture.h"
#include "Base/Include/Resource/BaseAudio.h"

#include "Base/Include/Other/BaseDraw.h"

#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

enum EffectType {
	// エフェクト無し
	NoEffect,
};

namespace effect {
	class BaseEffect
	{

	public: // メンバ関数

		// コンストラクタ
		//BaseEffect();
		// デストラクタ
		//~BaseEffect();

		// 初期化
		void BaseInitialize();
		void BaseInitialize(Point _position);
		virtual void Initialize();
		// 更新
		void BaseUpdate();
		virtual void Update();
		// 描画
		void BaseDraw();
		virtual void Draw();

		// エフェクトを終了させる関数
		// 返り値：なし
		// 引数：
		void EndEffect();

		// エフェクトが終了したかどうかを返す関数
		// 返り値：終了したならtrue、そうでなければfalse
		// 引数：無し
		// エフェクトが完了したかをチェックする関数
		bool isEndEffect();



	protected: // メンバ変数

		// 描画座標
		Point position;
		// 現在の経過フレーム
		int elapsedFrame;

		// エフェクトが終了したかどうか
		bool isEnd;
	};
}

using namespace effect;