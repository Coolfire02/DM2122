#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vertex.h"

struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f)
	{
		Set(r, g, b);
	}
	void Set(float r, float g, float b)
	{
		this->r = r; this->g = g; this->b = b;
	}
};

/*
/ Materials should have componenets of the ones listed below
*/
struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;
	Material() {
		kShininess = 0.0f;
	};
};


#endif