#include "Entity.h"
#include <iostream>

Entity::Entity(Scene* associatedScene) : scene(associatedScene) {
}

Entity::~Entity() {

}

bool Entity::isDead() {
	return isDead;
}