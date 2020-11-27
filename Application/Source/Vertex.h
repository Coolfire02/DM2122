#pragma once

#include "Vector3.h"

struct Position
{
	float x, y, z;
	Position(float x = 0, float y = 0, float z = 0) : x{ x }, y{ y }, z{ z } {};
	void set(float x = 0, float y = 0, float z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	};
};

struct Color
{
	float r, g, b;
	Color(float r = 0, float g = 0, float b = 0) : r{ r }, g{ g }, b{ b } {};
	void set(float r = 0, float g = 0, float b = 0) {
		this->r = r;
		this->g = g;
		this->b = b;
	};
};

struct Vertex
{
	Position pos;
	Color color;
	Vector3 normal;

};