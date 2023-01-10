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
	// 全てのオブジェクトの実態を（Objectで）初期化
	void Initialize();
	// 更新
	// 全てのオブジェクトを更新（Updateを呼び出す）
	void Update();
	// 描画
	// 全てのオブジェクトを描画（Drawを呼び出す）
	void Draw();


	// 新しいオブジェクトのインスタンスを生成する関数たち
	// 中の実態がObjectのものを若い数字優先で上書きしていく
	

	// Block
	void MakeNewObjectBlock(Point position, Point size);

	// Player
	void MakeNewObjectPlayer(Point position);



private: // メンバ定数

	const static int kMaxObjectSize = 256;

private: // メンバ変数

	// オブジェクトのポインタ達
	Object* object[kMaxObjectSize];

};