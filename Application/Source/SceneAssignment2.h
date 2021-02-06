#ifndef SCENE_ASSIGNMENT2_H
#define SCENE_ASSIGNMENT2_H

#include "Scene.h"
#include "FirstPersonCamera.h"	
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "EntityManager.h"

//Entities
#include "Sonic.h"
#include "Coin.h"

#include "MeshHandler.h"

class SceneAssignment2 : public Scene
{
	enum SCENE_GEOMETRY_TYPE
	{
		//General
		GEO_AXES = 0,

		//Sonic Characters
		GEO_SONIC_EGGMAN,
		GEO_SONIC_TAILS,

		//Platform
		GEO_PLATFORM_FLOOR,
		GEO_OBJ_WINNERPODIUM,
		GEO_OBJ_FENCE,
		GEO_OBJ_GRASS,
		GEO_OBJ_DIRT,

		//UI
		GEO_ICON,
		GEO_TEXT,
		GEO_COINS_METER,
		GEO_TIME_METER,

		//Skybox
		GEO_SKY_LEFT,
		GEO_SKY_RIGHT,
		GEO_SKY_TOP,
		GEO_SKY_BOTTOM,
		GEO_SKY_FRONT,
		GEO_SKY_BACK,

		GEO_LIGHTBALL,
		NUM_GEOMETRY,
	};

private:

	FirstPersonCamera camera;
	EntityManager eManager;
	Entity* player;


	Mesh* meshList[NUM_GEOMETRY];
	Light light[2];

	bool hitboxEnable;
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