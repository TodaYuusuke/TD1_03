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

};