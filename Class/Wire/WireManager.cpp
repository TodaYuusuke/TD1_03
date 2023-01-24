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

}

void WireManager::Update(ObjectManager* objectManager, Boss* boss) {
	for (int i = 0; i < BaseConst::kWireMaxAmount; i++) {
		wires[i]->Update(objectManager, boss);
	}

}

void WireManager::Draw() {
	for (int i = 0; i < BaseConst::kWireMaxAmount; i++) {
		wires[i]->Draw();
	}
}

int WireManager::Shot(Point shotPosition, float shotAngle,Player* _player) {
	for (int i = 0; i < BaseConst::kWireMaxAmount; i++) {
		switch (wires[i]->Shot(shotPosition, shotAngle, _player))
		{
			case 1:
				return 1;
			case -1:
				return -1;
			case -2:
				break;
		}
	}
	return -2;
}

void WireManager::Attract() {
	for (int i = 0; i < BaseConst::kWireMaxAmount; i++) {
		wires[i]->Attract();
	}
}