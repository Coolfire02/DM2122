#include "Position3D.h"

Position3D::Position3D(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Position3D::Position3D() : x(0),y(0),z(0) {}
Position3D::~Position3D() {} //Intentionally left blank

void Position3D::setX(int x) {
	this->x = x;
}

void Position3D::setY(int y) {
	this->y = y;
}

void Position3D::setZ(int z) {
	this->z = z;
}

int Position3D::getX() {
	return x;
}

int Position3D::getY() {
	return y;
}

int Position3D::getZ() {
	return z;
}
