#include "EntityManager.h"

EntityManager::EntityManager(Scene* scene) : scene(scene) {

}

EntityManager::~EntityManager() {
	for (auto& entry : worldEntities) {
		delete entry;
	}
	for (auto& entry : movingEntities) {
		delete entry;
	}
}

void EntityManager::spawnMovingEntity(Entity* e) {
	movingEntities.push_back(e);
}

void EntityManager::spawnWorldEntity(Entity* e) {
	worldEntities.push_back(e);
}

std::vector<Entity*> EntityManager::getEntities() {
	std::vector<Entity*> v(movingEntities);
	v.insert(v.end(), worldEntities.begin(), worldEntities.end());
	return v;
}

std::vector<CollidedWith*> EntityManager::preCollisionUpdate() {
	
	//OldTick
	for (auto& entry : prevTick) {
		delete entry;
	}
	prevTick.clear();
	prevTick = thisTick;
	thisTick.clear();

	for (auto& movingE : movingEntities) {
		for (auto& worldE: worldEntities) {
			if (movingE->getHitBox().collidedWith(worldE->getHitBox())) {
				thisTick.push_back(new CollidedWith(movingE, worldE, true));
			}
		}
	}
	return thisTick;
}