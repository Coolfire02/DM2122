#include "Coin.h"

//Speed is the amount of rounds to spin per second
Coin::Coin(Scene* scene, Box* hitBox, std::string name) : Entity(scene, ENTITYTYPE::COIN, name), spin(true), speed(1.5f) {
	this->hitBox = new HitBox(hitBox);
}
	
Coin::~Coin() {}

void Coin::setSpin(bool toggle) {
	spin = toggle;
}

void Coin::setSpinSpeed(float speed) {
	this->speed = speed;
}

bool Coin::isSpinning() {
	return spin;
}

void Coin::Update(double dt) {
	if (spin) {
		rot += speed / 360.0 * dt;
		if (rot > 360) rot -= 360;
		this->data->rotYMag = rot;
	}
}

void Coin::Render() {
	this->scene->modelStack.PushMatrix();
		this->loadOriginTRSIntoStacknHitBox();
		this->scene->RenderMesh(MeshHandler::getMesh(GEO_COIN), this->scene->isLightEnabled());
	this->scene->modelStack.PopMatrix();
}
