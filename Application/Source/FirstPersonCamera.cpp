#include "FirstPersonCamera.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
FirstPersonCamera::FirstPersonCamera()
{

}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
FirstPersonCamera::~FirstPersonCamera()
{
}

/******************************************************************************/
/*!
\brief
Initialize FirstPersonCamera

\param pos - position of FirstPersonCamera
\param target - where the FirstPersonCamera is looking at
\param up - up vector of FirstPersonCamera
*/
/******************************************************************************/
void FirstPersonCamera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->view = (target - pos).Normalized();
	this->right = view.Cross(up).Normalized();
	this->up = right.Cross(view).Normalized();
}



/******************************************************************************/
/*!
\brief
Reset the FirstPersonCamera settings
*/
/******************************************************************************/
void FirstPersonCamera::Reset()
{
}

/******************************************************************************/
/*!
\brief
To be called every frame. FirstPersonCamera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void FirstPersonCamera::Update(double dt)
{
	static const float CAMERA_SPEED = 100.f;
	if (Application::IsKeyPressed('W')) {
		
	}
	if (Application::IsKeyPressed('A')) {
		Mtx44 rotation;
		rotation.SetToRotation(CAMERA_SPEED * (float)dt, right.x, right.y, right.z);
		up = rotation * up;

	}
	if (Application::IsKeyPressed('D')) {

	}
	if (Application::IsKeyPressed('S')) {

	}
	if (Application::IsKeyPressed('M')) {

	}
	if (Application::IsKeyPressed('N')) {

	}


}

void FirstPersonCamera::Follow(float x, float y, float z) {

	target.Set(x, y, z);
	Vector3 dir = target - position;
	Vector3 right = dir.Cross(Vector3(0.0, 1.0f, 0.0f));
	Vector3 up = right.Cross(dir);
	this->Init(position, target, up);
}