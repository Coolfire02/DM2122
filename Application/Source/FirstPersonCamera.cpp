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
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up).Normalized();
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
	static const float CAMERA_SPEED = 45.f;
	static const float ZOOM_SPEED = 20.f;
	if (Application::IsKeyPressed('W')) {
		float pitch = CAMERA_SPEED * static_cast<float>(dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = position + view;
	}
	if (Application::IsKeyPressed('A')) {
		float yaw = CAMERA_SPEED * static_cast<float>(dt);
		Vector3 view = (target - position).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		up = rotation * up;
	}
	if (Application::IsKeyPressed('D')) {
		float yaw = -CAMERA_SPEED * static_cast<float>(dt);
		Vector3 view = (target - position).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		up = rotation * up;
	}
	if (Application::IsKeyPressed('S')) {
		float pitch = -CAMERA_SPEED * static_cast<float>(dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = position + view;
	}
	if (Application::IsKeyPressed('M')) {
		Vector3 view = (target - position).Normalized();
		position += view * (float)dt * CAMERA_SPEED * 0.3;
		target = position + view;
	}
	if (Application::IsKeyPressed('N')) {
		Vector3 view = (target - position).Normalized();
		position -= view * (float)dt * CAMERA_SPEED * 0.3;
		target = position + view;
	}
	if (Application::IsKeyPressed('V')) { //Strafing left
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();

		position += right * (float)dt * CAMERA_SPEED * 0.3;
		target = position + view;
	}
	if (Application::IsKeyPressed('B')) { //Strafing right
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();

		position -= right * (float)dt * CAMERA_SPEED * 0.3;
		target = position + view;
	}




}

void FirstPersonCamera::Follow(float x, float y, float z) {

	target.Set(x, y, z);
	Vector3 dir = target - position;
	Vector3 right = dir.Cross(Vector3(0.0, 1.0f, 0.0f));
	Vector3 up = right.Cross(dir);
	this->Init(position, target, up);
}