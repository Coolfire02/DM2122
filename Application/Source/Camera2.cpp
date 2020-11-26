#include "Camera2.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera2::Camera2()
{

}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera2::~Camera2()
{
}

/******************************************************************************/
/*!
\brief
Initialize Camera2

\param pos - position of Camera2
\param target - where the Camera2 is looking at
\param up - up vector of Camera2
*/
/******************************************************************************/
void Camera2::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up).Normalized();
	this->up = right.Cross(view).Normalized();
}

/******************************************************************************/
/*!
\brief
Reset the Camera2 settings
*/
/******************************************************************************/
void Camera2::Reset()
{
}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera2 will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera2::Update(double dt)
{
	static const float CAMERA_SPEED = 45.f;
	if (Application::IsKeyPressed('W')) {
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(- CAMERA_SPEED * dt , right.x, right.y, right.z);
		position = rotation * position;
		up = right.Cross(view).Normalized(); //update the UP with new y as its no longer 0,1,0 when it surrounds obj
	}
	if (Application::IsKeyPressed('A')) {
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(- CAMERA_SPEED * dt, 0, 1, 0);
		position = rotation * position;
		up = rotation * up;
	}
	if (Application::IsKeyPressed('D')) {
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(CAMERA_SPEED * dt, 0, 1, 0);
		position = rotation * position;
		up = rotation * up;
	}
	if (Application::IsKeyPressed('S')) {
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up).Normalized();
		right.y = 0;
		right.Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(CAMERA_SPEED * dt, right.x, right.y, right.z);
		position = rotation * position;
		up = right.Cross(view).Normalized();
	}
	if (Application::IsKeyPressed('M')) {
		Vector3 view = (target - position).Normalized();
		position += view * dt * CAMERA_SPEED*0.2;
	}
	if (Application::IsKeyPressed('N')) {
		Vector3 view = (target - position).Normalized();
		position -= view * dt * CAMERA_SPEED*0.2;
	}

}