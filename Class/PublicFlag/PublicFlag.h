#pragma once

////////////////////////////////////////////////////////////////////////////////
/////　　クラス同士などで情報の受け渡しがめんどくさいときに無理やり受け渡しするクラス　　/////
////////////////////////////////////////////////////////////////////////////////

class PublicFlag {
public: // 全てstaticでpublic
	// 初期化（inline記述）
	static void Initialize() {
		kBossisTurningAndCutWire = false;
		kisStaging = false;
	}

	// 演出中フラグ
	static bool kisStaging;
	
	// ボスが回転中で、ワイヤーを千切る処理がONの間trueにする
	static bool kBossisTurningAndCutWire;
	
};