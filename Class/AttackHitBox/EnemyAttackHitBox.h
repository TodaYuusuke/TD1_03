#pragma once
#include "MyBase/MyBase.h"

// ボスの生成する当たり判定を管理するクラス

class EnemyAttackHitBox {
public: // メンバ関数

	// 初期化
	static void Initialize();
	// 更新
	static void Update();
	// 描画
	static void Draw();

	// 新しく当たり判定を追加する関数（四角）
	// 引数：
	// centerPosition ... 真ん中の座標
	// width ... ヒットボックスの横幅（左上の点から）
	// height ... ヒットボックスの縦幅（左上の点から）
	// angle ... ヒット対象の四角の回転角度
	// atk ... ダメージ量
	static void MakeNewHitBox(Point centerPosition, float width, float height, float angle, float atk);

	// 新しく当たり判定を追加する関数（左の円）
	// 引数：
	// centerPosition ... 真ん中の座標
	// width ... ヒットボックスの横幅（左上の点から）
	// height ... ヒットボックスの縦幅（左上の点から）
	// angle ... ヒット対象の四角の回転角度
	// atk ... ダメージ量
	static void MakeNewHitBoxLeft(Point centerPosition, float radius, float angle, float atk);
	// 新しく当たり判定を追加する関数（右の円）
	// 引数：
	// centerPosition ... 真ん中の座標
	// width ... ヒットボックスの横幅（左上の点から）
	// height ... ヒットボックスの縦幅（左上の点から）
	// angle ... ヒット対象の四角の回転角度
	// atk ... ダメージ量
	static void MakeNewHitBoxRight(Point centerPosition, float radius, float angle, float atk);


	// 当たり判定検証
	// 返り値：ヒットしていた場合 -> 被ダメージ量、　ヒットしていない場合 -> 0
	// 引数：
	// centerPosition ... 検証する座標
	static float CheckHitBox(Point centerPosition);

private: // メンバ変数

	// 現在の添え字
	static int num;

	struct HitBox {
		Point centerPosition;
		float width;
		float height;
		float angle;
		float atk;
	};
	// 当たり判定のリスト
	static HitBox hitBox[128];


	struct HitEllipse {
		Point centerPosition;
		float radius;
		float angle;
		float atk;
	};

	// 左の半円の当たり判定
	static HitEllipse leftEllipse;
	// 右の半円の当たり判定
	static HitEllipse rightEllipse;
};