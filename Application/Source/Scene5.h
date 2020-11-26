#ifndef SCENE_5_H
#define SCENE_5_H

#include "Scene.h"
#include "Camera2.h"	
#include "MeshBuilder.h"
#include "MatrixStack.h"

class Scene5 : public Scene
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
	GEO_SUN,
	GEO_PLANET1,
	GEO_PLANET2,
	GEO_PLANET3,
	GEO_PLANET4,
	GEO_PLANET5,
	GEO_PLANET6,
	GEO_PLANET7,
	GEO_PLANET8,
	GEO_PLANET9,
	GEO_PLANET10,
	GEO_PLANET11,

	NUM_GEOMETRY,
};

private:

	Camera2 camera;

	unsigned m_vertexArrayID;
	unsigned m_programID;

	//stores handlers for uniform parametes
	unsigned m_parameters[U_TOTAL];

	Mesh* meshList[NUM_GEOMETRY];
	MS modelStack, viewStack, projectionStack;

	bool rotateAngleFWD;
	bool translateZFWD;
	bool scaleALLFWD;
	float rotateAngle;
	float rotateAngle2;
	float translateZ;
	float scaleAll;

public:
	Scene5();
	~Scene5();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif