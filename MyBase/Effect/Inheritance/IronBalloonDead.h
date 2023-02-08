#pragma once
#include "MyBase/MyBase.h"
#include "MyBase/Effect/BaseEffect.h"

namespace effect {
	class IronBalloonDead :
		public BaseEffect {
	public: // メンバ関数

		// コンストラクタ
		IronBalloonDead(Point, bool);
		// デストラクタ
		~IronBalloonDead();


		// 初期化
		void Initialize() override;
		// 更新
		void Update() override;
		// 描画
		void Draw() override;

	private: // メンバ変数
		// 右向きかどうか
		bool isRight;
	};
}