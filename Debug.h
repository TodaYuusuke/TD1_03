#include "MyBase/Include/MyBase.h"
#include "Class/Include/Object/ObjectManager.h"
#include "Class/Include/Wire/WireManager.h"

#include "Class/Include/Map/MapManager.h"

// 自分で開発する際に、デバッグ用の処理はこちらで用意すること。
// 開発中のclassのインスタンスなどをここで呼び出し、試したい関数を自分で呼び出すコードを書くこと。

class Debug {

public: // メンバ関数

	// コンストラクタ
	Debug();
	// デストラクタ
	~Debug();

	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();


private: // メンバ変数


	ObjectManager objectManager;
	WireManager wireManager;

};