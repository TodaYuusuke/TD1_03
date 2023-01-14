#include "Class/Include/Wire/WireManager.h"

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

bool WireManager::Shot(Point shotPosition, float shotAngle,Player* _player) {
	for (int i = 0; i < BaseConst::kWireMaxAmount; i++) {
		if (wires[i]->Shot(shotPosition, shotAngle, _player)) {
			return true;
		}
	}
	return false;
}

void WireManager::Attract() {

}