#pragma once
#include "MyBase/MyBase.h"
#include "MyBase/Effect/BaseEffect.h"

namespace effect {
	class FadeIn :
		public BaseEffect {
	public: // メンバ関数

		// コンストラクタ
		FadeIn();
		// デストラクタ
		~FadeIn();


		// 初期化
		void Initialize() override;
		// 更新
		void Update() override;
		// 描画
		void Draw() override;

	private: // メンバ変数
		
		// 現在の透明度
		int alpha;
	};
}