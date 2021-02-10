#ifndef SCENE_ASSIGNMENT2_H
#define SCENE_ASSIGNMENT2_H

#include <map>

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
	enum INTERACTION_TYPE {
		EGGMAN,
		TAILS,
		SHOP,
		RACE,
		INTERACTION_COUNT,
	};

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
	int upgradeCost[10];
	const float defaultSpeed;
	float playerSpeed;
	int playerSpeedLevel;
	const int maxPlayerSpeedLevel;
	std::vector<float> racingScores; //These are collected through gameplay
	int coinBalance;

	//Scene object specific animation variables
	float shoeShopX, shoeShopY, shoeShopZ;
	float shoeRotation;
	float shoeYOffset;

	//Rainbow calculations
	float rainbow;

	//Interaction
	bool canInteractWithSomething;

	//Queued Message, commands to execute when message is brought up
	//Add a "CLOSENOW" message to have "Final Execution commands". (Aka commands to execute on close)
	std::vector<std::string, std::vector<std::string>> queuedMessages;
	int currentMessage;

	bool isInteracting;
	float interactionTime;
	GEOMETRY_TYPE characterOnUI; //When interacting if there is a person talking to you

	Mesh* meshList[NUM_GEOMETRY];
	Light light[3];

	bool hitboxEnable;
	float fps;
	
	void RenderSkybox();


public:
	SceneAssignment2();
	~SceneAssignment2();

	int getCoins();
	void setCoins(int);
	void addCoins(int);

	bool runCommand(std::string cmd);
	bool upgradeSpeed();
	bool loadInteractions(INTERACTION_TYPE type);

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif