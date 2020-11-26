#include "Camera.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera::Camera()
{

}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera::~Camera()
{
}

/******************************************************************************/
/*!
\brief
Initialize camera

\param pos - position of camera
\param target - where the camera is looking at
\param up - up vector of camera
*/
/******************************************************************************/
void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
}

/******************************************************************************/
/*!
\brief
Reset the camera settings
*/
/******************************************************************************/
void Camera::Reset()
{
}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera::Update(double dt)
{
	if (GetKeyState('W') & 0x8000) {
		this->position.y += 10.f * dt;
	}else if (GetKeyState('A') & 0x8000) {
		this->position.x -= 10.f * dt;
	}else if (GetKeyState('D') & 0x8000) {
		this->position.x += 10.f * dt;
	}else if (GetKeyState('S') & 0x8000) {
		this->position.y -= 10.f * dt;
	}
	else if (GetKeyState('M') & 0x8000) {
		this->position.z += 10.f * dt;
	}
	else if (GetKeyState('N') & 0x8000) {
		this->position.z -= 10.f * dt;
	}

}