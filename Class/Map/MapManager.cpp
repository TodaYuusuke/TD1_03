#include "Class/Map/MapManager.h"

// �R���X�g���N�^
MapManager::MapManager() {

}
// �f�X�g���N�^
MapManager::~MapManager() {

}


// ������
void MapManager::Initialize() {
	for (int y = 0; y < BaseConst::kBossStageSizeHeight; y++) {
		for (int x = 0; x < BaseConst::kBossStageSizeWidth; x++) {
            map[y][x].Initialize((MapChipType)BaseConst::kBossStageData[y][x]);
		}
	}
}
// �X�V
void MapManager::Update() {
	for (int y = 0; y < BaseConst::kBossStageSizeHeight; y++) {
		for (int x = 0; x < BaseConst::kBossStageSizeWidth; x++) {
			map[y][x].Update();
		}
	}
}
// �`��
void MapManager::Draw() {
	for (int y = 0; y < BaseConst::kBossStageSizeHeight; y++) {
		for (int x = 0; x < BaseConst::kBossStageSizeWidth; x++) {
            // ������ʊO�̏ꍇ�͕`�悵�Ȃ�
            Point drawPosition = { (float)x * BaseConst::kMapChipSizeWidth, (float)(BaseConst::kBossStageSizeHeight - y) * BaseConst::kMapChipSizeHeight};
            drawPosition = BaseDraw::WorldtoScreen(drawPosition);

            if (drawPosition.y > 0 - BaseConst::kMapChipSizeHeight) {
                if (drawPosition.y < BaseConst::kWindowHeight + BaseConst::kMapChipSizeHeight) {
                    if (drawPosition.x > 0 - BaseConst::kMapChipSizeWidth) {
                        if (drawPosition.x < BaseConst::kWindowWidth + BaseConst::kMapChipSizeWidth) {
                            map[y][x].Draw(BaseDraw::ScreentoWorld(drawPosition), GetMapChipType(y, x));
                        }
                    }
                }
            }
		}
	}
}

/// <summary>
/// �w�肵�����W���}�b�v�Ƀq�b�g���Ă��邩�ǂ���
/// </summary>
/// <param name="hitPosition �����蔻����m�F���郏�[���h���W"></param>
/// <returns>�q�b�g���Ă����ꍇ ... true�A�q�b�g���Ă��Ȃ������ꍇ ... false</returns>
bool MapManager::CheckHitBox(Point hitPosition) {

    int y = BaseConst::kBossStageSizeHeight - (hitPosition.y / BaseConst::kMapChipSizeHeight);
    int x = hitPosition.x / BaseConst::kMapChipSizeWidth;

    if (y < 0 || y >= BaseConst::kBossStageSizeHeight) {
        return false;
    }
    if (x < 0 || x >= BaseConst::kBossStageSizeWidth) {
        return false;
    }

    hitPosition.x -= x * BaseConst::kMapChipSizeWidth;
    hitPosition.y -= (BaseConst::kBossStageSizeHeight - y - 1) * BaseConst::kMapChipSizeHeight;

    return map[y][x].CheckHitBox(hitPosition);
}



// �}�b�v�`�b�v�̌`�����肷��֐�
int MapManager::GetMapChipType(int y, int x) {

    // �㉺���E�������`�b�v�����L�^����ϐ�
    bool up, down, left, right;

    // ��O����Ȃ����`�F�b�N
    if (y - 1 < 0) {
        // ��O�Ȃ�Ώ�͂���Ɖ��肷��
        up = true;
    }
    // �オ�����`�b�v�����m�F
    else {
        if (map[y][x].type == map[y - 1][x].type) {
            up = true;
        }
        else {
            up = false;
        }
    }

    // ��O����Ȃ����`�F�b�N
    if (y + 1 >= BaseConst::kBossStageSizeHeight) {
        // ��O�Ȃ�Ή��͂���Ɖ��肷��
        down = true;
    }
    // ���������`�b�v�����m�F
    else {
        if (map[y][x].type == map[y + 1][x].type) {
            down = true;
        }
        else {
            down = false;
        }
    }

    // ��O����Ȃ����`�F�b�N
    if (x - 1 < 0) {
        // ��O�Ȃ�΍��͂���Ɖ��肷��
        left = true;
    }
    // ���������`�b�v�����m�F
    else {
        if (map[y][x].type == map[y][x - 1].type) {
            left = true;
        }
        else {
            left = false;
        }
    }

    // ��O����Ȃ����`�F�b�N
    if (x + 1 >= BaseConst::kBossStageSizeWidth) {
        // ��O�Ȃ�ΉE�͂���Ɖ��肷��
        right = true;
    }
    // �E�������`�b�v�����m�F
    else {
        if (map[y][x].type == map[y][x + 1].type) {
            right = true;
        }
        else {
            right = false;
        }
    }



    // �e������̃p�^�[������

    // �S��������
    if (up && down && left && right) {
        return 0;
    }

    // ��̂ݖ���
    else if (!up && down && left && right) {
        return 1;
    }
    // �E�̂ݖ���
    else if (up && down && left && !right) {
        return 2;
    }
    // ���̂ݖ���
    else if (up && !down && left && right) {
        return 3;
    }
    // ���̂ݖ���
    else if (up && down && !left && right) {
        return 4;
    }

    // ��ƉE�̂ݖ���
    else if (!up && down && left && !right) {
        return 5;
    }
    // �E�Ɖ��̂ݖ���
    else if (up && !down && left && !right) {
        return 6;
    }
    // ���ƍ��̂ݖ���
    else if (up && !down && !left && right) {
        return 7;
    }
    // ���Ə�̂ݖ���
    else if (!up && down && !left && right) {
        return 8;
    }

    // ���̂ݗL��
    else if (!up && down && !left && right) {
        return 9;
    }
    // ���̂ݗL��
    else if (!up && !down && left && !right) {
        return 10;
    }
    // ��̂ݗL��
    else if (up && !down && !left && !right) {
        return 11;
    }
    // �E�̂ݗL��
    else if (!up && !down && !left && right) {
        return 12;
    }

    // �S�����Ȃ�
    else {
        return 13;
    }
}




// �}�b�v�̔z��
Map MapManager::map[BaseConst::kBossStageSizeHeight][BaseConst::kBossStageSizeWidth];