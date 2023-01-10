#include "MyBase/Include/MyBase.h"

// ワイヤーのクラス

class Wire {
public: // メンバ関数

	// コンストラクタ
	Wire();
	// デストラクタ
	~Wire();

	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();

private: // メンバ変数

	// 1点目の座標
	Point* firstPosition;
	// 2点目の座標
	Point* SecondPosition;



};