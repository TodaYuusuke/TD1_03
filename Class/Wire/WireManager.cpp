#include "Class/Wire/WireManager.h"

WireManager::WireManager() {

}

WireManager::~WireManager() {

}

void WireManager::Initialize() {
	for (int i = 0; i < BaseConst::kWireMaxAmount; i++) {
		wires[i] = new Wire();
		wires[i]->Initialize();
	}

	index = 0;
}

void WireManager::Update(ObjectManager* objectManager) {
	for (int i = 0; i < BaseConst::kWireMaxAmount; i++) {
		wires[i]->Update(objectManager);
	}

}

void WireManager::Draw() {
	for (int i = 0; i < BaseConst::kWireMaxAmount; i++) {
		wires[i]->Draw();
	}
}

int WireManager::Shot(Point shotPosition, float shotAngle, Player* _player) {
	// Œp‘±ƒtƒ‰ƒO
	int contineFlag = 0;
	
	do {
		switch (wires[index]->Shot(shotPosition, shotAngle, _player))
		{
			case 1:
				return 1;
			case -1:
				return -1;
			case -2:
				index++;
				if (index >= BaseConst::kWireMaxAmount) {
					index = 0;
				}
				contineFlag++;
				if (contineFlag >= BaseConst::kWireMaxAmount) {
					return -2;
				}

				break;
		}
	} while (contineFlag);

	return -2;
}

void WireManager::Attract() {
	for (int i = 0; i < BaseConst::kWireMaxAmount; i++) {
		wires[i]->Attract();
	}
}