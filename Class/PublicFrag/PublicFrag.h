#pragma once

////////////////////////////////////////////////////////////////////////////////
/////　　クラス同士などで情報の受けkBussisTurningAndCutWire要素を無理やり受け渡しするクラス　　/////
////////////////////////////////////////////////////////////////////////////////

class PublicFrag {
public: // 全てstaticでpublic
	// 初期化（inline記述）
	static void Initialize() {
		kBossisTurningAndCutWire = false;
	}

	// ボスが回転中で、ワイヤーを千切る処理がONの間trueにする
	static bool kBossisTurningAndCutWire;

};