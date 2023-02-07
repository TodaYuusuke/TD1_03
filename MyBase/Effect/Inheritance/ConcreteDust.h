#pragma once
#include "MyBase/MyBase.h"
#include "MyBase/Effect/BaseEffect.h"

#include "Class/Map/MapManager.h"

namespace effect {
	class ConcreteDust :
		public BaseEffect {
	public: // メンバ関数

		// コンストラクタ
		ConcreteDust(Point);
		// デストラクタ
		~ConcreteDust();


		// 初期化
		void Initialize() override;
		// 更新
		void Update() override;
		// 描画
		void Draw() override;

	private: // メンバ変数
		
		// 粒子の中心座標
		Point pos[BaseConst::kConcreteDustNum];
		// 速度
		Point vel[BaseConst::kConcreteDustNum];
		// 大きさ 1 ～ 3
		float size[BaseConst::kConcreteDustNum];

	};
}