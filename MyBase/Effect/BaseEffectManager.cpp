#include "MyBase/Effect/BaseEffectManager.h"


// 初期化
void BaseEffectManager::Initialize() {
	for (int i = 0; i < effectArraySize; i++) {
		effects[i] = new BaseEffect();
		effects[i]->BaseInitialize();
	}

	nextIndex = -1;
}
// 更新
void BaseEffectManager::Update() {
	for (int i = 0; i < effectArraySize; i++) {
		effects[i]->BaseUpdate();
	}
}
// 描画
void BaseEffectManager::Draw() {
	for (int i = 0; i < effectArraySize; i++) {
		effects[i]->BaseDraw();
	}
}



// 新規エフェクト登録関数
// 返り値：エフェクトがセットされた番号
// 引数：
// position ... 中心のワールド座標
// angle ... 回転角度（Degree）
// effectType ... エフェクトの種類
int BaseEffectManager::MakeNewEffect(Point position, EffectType effectType) {

	// 追加するまでループ
	while (true) {

		nextIndex++;
		if (nextIndex >= effectArraySize) {
			nextIndex = 0;
		}

		if (effects[nextIndex]->isEndEffect()) {
			switch (effectType)
			{
				case EffectType::NoEffect:
				default:
					break;
			}
			break;
		}

	}

	return nextIndex;
}


// エフェクトを終了させる関数
// 返り値：なし
// 引数：
// effectNum ... エフェクト番号
void BaseEffectManager::EndEffect(int effectNum) {
	return effects[effectNum]->EndEffect();
}


// エフェクトが終了したかを調べる関数
// 返り値：エフェクトが終了済み ... true 、 そうでない場合 ... false
// 引数：
// effectNum ... エフェクト番号
bool BaseEffectManager::isEndEffect(int effectNum) {
	return effects[effectNum]->isEndEffect();
}


//////////////////////////////////
/* - staticメンバ変数の実態を宣言 - */
//////////////////////////////////

// エフェクトの配列
BaseEffect* BaseEffectManager::effects[effectArraySize];
// 次に追加するエフェクトの添字
int BaseEffectManager::nextIndex;