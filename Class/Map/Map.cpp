#include "Class/Map/Map.h"

// �R���X�g���N�^
Map::Map() {
    Initialize(kTypeAir);
}
// �f�X�g���N�^
Map::~Map() {

}



// ������
void Map::Initialize(MapChipType type) {
    this->type = type;
}
// �X�V
void Map::Update() {

}
// �`��
void Map::Draw(Point drawPosition, int drawImageNum) {

    // �Ƃ肠�����i��œ���Ȍ`�̃}�b�v�`�b�v����������ꍇ�͏�����ǋL����j
    switch (type)
    {
        case kTypeAir:
            break;
        case kTypeNormal:
            BaseDraw::DrawSprite(drawPosition, BaseTexture::kTextureMapChipSample[drawImageNum], { 1,1 }, 0, WHITE);
            break;
        case kTypeFloor:
            BaseDraw::DrawSprite(drawPosition, BaseTexture::kTextureMapChipSample[drawImageNum], { 1,1 }, 0, WHITE);
            break;
        default:
            break;

    }
}

/// <summary>
/// �w�肵�����W���}�b�v�Ƀq�b�g���Ă��邩�ǂ���
/// </summary>
/// <param name="hitPosition �����蔻����m�F������W"></param>
/// <returns></returns>
bool Map::CheckHitBox(Point playerPosition) {

    // �Ƃ肠�����i��œ���Ȍ`�̃}�b�v�`�b�v����������ꍇ�͏�����ǋL����j
    switch (type)
    {
        case kTypeAir:
            return false;
        case kTypeNormal:
            return true;
        default:
            return false;
    }
}