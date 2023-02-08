#include "Class/Map/Map.h"

// コンストラクタ
Map::Map() {
	Initialize(kTypeAir);
}
// デストラクタ
Map::~Map() {

}



// 初期化
void Map::Initialize(MapChipType type) {
	this->type = type;
}
// 更新
void Map::Update() {

}
// 描画
void Map::Draw(Point drawPosition, int drawImageNum) {

	// とりあえず（後で特殊な形のマップチップを実装する場合は処理を追記する）
	switch (type)
	{
		case kTypeAir:
			break;
		case kTypeNormal:
			BaseDraw::DrawSprite(drawPosition, BaseTexture::kTextureMapChip[drawImageNum], { 1,1 }, 0, WHITE);
			break;
		case kTypeWall:
			BaseDraw::DrawSprite(drawPosition, BaseTexture::kTextureMapChip[drawImageNum], { 1,1 }, 0, 0xAAAAAAFF);
			break;
		case kTypeWeak:
			BaseDraw::DrawSprite(drawPosition, BaseTexture::kTextureMapChip[drawImageNum], { 1,1 }, 0, WHITE);
			BaseDraw::DrawSprite(drawPosition, BaseTexture::kTextureMapChipWeak, { 1,1 }, 0, WHITE);
			break;
		default:
			break;
	}
}

/// <summary>
/// 指定した座標がマップにヒットしているかどうか
/// </summary>
/// <param name="hitPosition 当たり判定を確認する座標"></param>
/// <param name="isBlock ヒットするのがBlockかどうか"></param>
/// <returns></returns>
bool Map::CheckHitBox(Point hitPosition, bool isBlock) {
	// とりあえず（後で特殊な形のマップチップを実装する場合は処理を追記する）
	switch (type)
	{
		case kTypeAir:
			return false;
		case kTypeNormal:
			return true;
		case kTypeWall:
			return false;
		case kTypeWeak:
			if (isBlock) {
				type = kTypeAir;
				PublicFlag::kBrokenConcretePlaySE = true;
			}
			return true;
		default:
			return false;
	}
}