#include "MyBase/Include/MyBase.h"
#include "Class/Include/Object/Object.h"

// いうまでもなくプレイヤー


// ヤマトへ


class Player :
	public Object {
public: // メンバ関数

	// コンストラクタ
	Player(Point centerPosition);
	// デストラクタ
	~Player();

	// 初期化
	void SuccessorInitialize() override;
	// 更新
	void SuccessorUpdate() override;
	// 描画
	void Draw() override;


private: // 関数

	// 移動関連
	void Move();
	// ワイヤーを射出する動作
	void ShotWire();

private: // メンバ変数

};