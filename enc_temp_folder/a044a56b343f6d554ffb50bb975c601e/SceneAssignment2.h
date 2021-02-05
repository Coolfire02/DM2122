#ifndef SCENE_ASSIGNMENT2_H
#define SCENE_ASSIGNMENT2_H

#include "Scene.h"
#include "FirstPersonCamera.h"	
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "EntityManager.h"
#include "MeshHandler.h"

class SceneAssignment2 : public Scene
{


	enum GEOMETRY_TYPE
	{
		GEO_AXES = 0,

		//Week 14
		GEO_TEXT,

		GEO_FLOOR,
		GEO_OBJ_WINNERPODIUM,
		GEO_OBJ_FENCE,

		GEO_OBJ_ISLAND,

		GEO_MODEL1,
		GEO_MODEL2,
		GEO_MODEL3,
		GEO_MODEL4,
		GEO_MODEL5,
		GEO_MODEL6,

		GEO_SKY_LEFT,
		GEO_SKY_RIGHT,
		GEO_SKY_TOP,
		GEO_SKY_BOTTOM,
		GEO_SKY_FRONT,
		GEO_SKY_BACK,

		GEO_ICON,

		GEO_SONIC_AMY,

		GEO_LIGHTBALL,
		NUM_GEOMETRY,
	};

private:

	FirstPersonCamera camera;
	EntityManager eManager;
	Entity* player;


	unsigned m_vertexArrayID;
	unsigned m_programID;

	//stores handlers for uniform parametes
	unsigned m_parameters[U_TOTAL];

	Mesh* meshList[NUM_GEOMETRY];
	Light light[2];
	//MS modelStack, viewStack, projectionStack;
	bool lightEnable;
	bool rotateAngleFWD;
	bool translateZFWD;
	bool scaleALLFWD;
	float rotateAngle;
	float rotateAngle2;
	float translateZ;
	float scaleAll;

	float fps;

	
	void RenderSkybox();


public:
	SceneAssignment2();
	~SceneAssignment2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif