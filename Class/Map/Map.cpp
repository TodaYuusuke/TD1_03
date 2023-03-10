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
        case kTypeFloor:
            BaseDraw::DrawSprite(drawPosition, BaseTexture::kTextureMapChipFloor, { 1,1 }, 0, WHITE);
            break;
        default:
            break;
    }
}

/// <summary>
/// 指定した座標がマップにヒットしているかどうか
/// </summary>
/// <param name="hitPosition 当たり判定を確認する座標"></param>
/// <returns></returns>
bool Map::CheckHitBox(Point hitPosition) {



    // とりあえず（後で特殊な形のマップチップを実装する場合は処理を追記する）
    switch (type)
    {
        case kTypeAir:
            return false;
        case kTypeNormal:
            return true;
        case kTypeWall:
            return false;
            break;
        case kTypeFloor:
            // 点が上辺より下で
            if (hitPosition.y > 12) {
                // 点が下辺より上で
                if (hitPosition.y < 19) {
                    // 点が左辺より右で
                    if (hitPosition.x > 0) {
                        // 点が右辺より左の場合 -> ヒットしている
                        if (hitPosition.x < 32) {
                            return true;
                        }
                    }
                }
            }
            return false;
        default:
            return false;
    }
}