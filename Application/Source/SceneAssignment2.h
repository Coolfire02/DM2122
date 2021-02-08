#ifndef SCENE_ASSIGNMENT2_H
#define SCENE_ASSIGNMENT2_H

#include "Scene.h"
#include "FirstPersonCamera.h"	
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"

#include "EntityManager.h"
#include "MeshHandler.h"

//Entities
#include "Sonic.h"
#include "Coin.h"
#include "NPC.h"
#include "CustomEntity.h"
#include "WorldObject.h"

class SceneAssignment2 : public Scene
{
	enum SCENE_GEOMETRY_TYPE
	{
		//General
		GEO_AXES = 0,

		//Platform
		GEO_OBJ_ISLAND,
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

	//Game
	const float defaultSpeed;
	float playerSpeed;

	std::vector<std::string> queuedMessages;
	bool isInteracting;
	float interactionTime;
	GEOMETRY_TYPE characterOnUI; //When interacting if there is a person talking to you

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