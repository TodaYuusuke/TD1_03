#pragma once
#include "MyBase/MyBase.h"
#include "MyBase/Effect/BaseEffect.h"

namespace effect {
	class WhirlWind :
		public BaseEffect {
	public: // メンバ関数

		// コンストラクタ
		WhirlWind();
		// デストラクタ
		~WhirlWind();


		// 初期化
		void Initialize() override;
		// 更新
		void Update() override;
		// 描画
		void Draw() override;

	private: // メンバ変数

		/* この範囲の変数は既に宣言されているので利用してくれ（ｺﾒﾝﾄｱｳﾄは外さなくてよし）
		// 描画座標
		Point position;
		// 現在の経過フレーム
		int elapsedFrame;

		// エフェクトが終了したかどうか
		bool isEnd;
		*/
	};
}