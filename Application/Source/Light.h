#ifndef LIGHT_H
#define LIGHT_H

#include "Vertex.h"

struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	Light() {
		position.set(0.0f, 20.0f, 0.0f);
		color.set(1.0f, 1.0f, 1.0f);
		power = 1;
		kC = 1.0f;
		kL = 0.01f;
		kQ = 0.001f;
	}
};

#endif