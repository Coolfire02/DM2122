#include "Entity.h"
#include <iostream>

Entity::Entity() {

}

Entity::~Entity() {

}

bool Entity::loadGeometries() {
	if (!loadedGeometries) {
		
		return true;
	}
	return false;
}

bool Entity::isDead() {
	return isDead;
}