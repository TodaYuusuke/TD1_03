#include "MyBase/Include/MyBase.h"
#include "Class/Include/Object/Object.h"

#include "Class/Include/Object/Block/Block.h"
#include "Class/Include/Object/Player/Player.h"



// プログラム内のオブジェクトを全て管理するクラス


class ObjectManager {

public: // メンバ関数

	// コンストラクタ
	ObjectManager();
	// デストラクタ
	~ObjectManager();

	// 初期化
	// 全てのオブジェクトの実態を初期化
	void Initialize();
	// 更新
	// 全てのオブジェクトを更新
	void Update();
	// 描画
	// 全てのオブジェクトを描画
	void Draw();


private: // メンバ定数

	const static int kMaxObjectSize = 256;

private: // メンバ変数

	// オブジェクトのポインタ達
	Object* object[kMaxObjectSize];

};