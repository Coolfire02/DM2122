#include "Entity.h"
#include <iostream>

Entity::Entity(Scene* associatedScene, ENTITYTYPE type) : scene(associatedScene), type(type), dead(false) {}

Entity::~Entity() {
}

EntityData Entity::getLocation() {
	return data;
}

HitBox Entity::getHitBox() {
	return hitBox;
}

bool Entity::isDead() {
	return dead;
}