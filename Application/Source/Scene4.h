#ifndef SCENE_4_H
#define SCENE_4_H

#include "Scene.h"
#include "Camera.h"	
#include "MeshBuilder.h"

class Scene4 : public Scene
{

enum UNIFORM_TYPE
{
	U_MVP = 0,
	U_TOTAL
};

enum GEOMETRY_TYPE
{
	GEO_CUBE = 0,
	GEO_AXES,
	GEO_CONE,
	GEO_SPHERE,
	NUM_GEOMETRY,
};

private:

	Camera camera;

	unsigned m_vertexArrayID;
	unsigned m_programID;

	//stores handlers for uniform parametes
	unsigned m_parameters[U_TOTAL];

	Mesh* meshList[NUM_GEOMETRY];


	bool rotateAngleFWD;
	bool translateZFWD;
	bool scaleALLFWD;
	float rotateAngle;
	float translateZ;
	float scaleAll;

public:
	Scene4();
	~Scene4();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif