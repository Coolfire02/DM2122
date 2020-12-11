#ifndef CAMERA_2_H
#define CAMERA_2_H

#include "Application.h"
#include "Vector3.h"
#include "Mtx44.h"

class Camera2
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;

	Camera2();
	~Camera2();
	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Reset();
	void Update(double dt);
	void Follow(float x, float y, float z);
};

#endif