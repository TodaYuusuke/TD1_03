#pragma once
#include "MyBase/MyBase.h"
#include "MyBase/Effect/BaseEffect.h"


namespace effect {
	class BlockBreak :
		public BaseEffect {
	public: // メンバ関数

		// コンストラクタ
		BlockBreak(Point);
		// デストラクタ
		~BlockBreak();


		// 初期化
		void Initialize() override;
		// 更新
		void Update() override;
		// 描画
		void Draw() override;

	private: // メンバ変数
		
		// スクラップの座標
		Point pos[BaseTexture::kBlockScrapAmount];
		// 速度
		Point velocity[BaseTexture::kBlockScrapAmount];
		// 回転角度
		float angle[BaseTexture::kBlockScrapAmount];
	};
}