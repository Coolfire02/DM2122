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

//Interactions are stored in a vector in this Scene, when an "Interaction" is loaded,
//a bunch of Interaction struct Objects are created to handle interaction.
//you can add pre, post commands to execute, as well as the text to display in this Interaction
struct Interaction {
	//Read up runCommand function for Command Params.
	//e.g. cmd: /givecoin 1 (Gives player 1 coin)
	std::vector<std::string> preInteractionCMD;
	std::string interactionText;
	std::vector<std::string> postInteractionCMD;
};

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
	bool raceUnlocked;
	int upgradeCost[10];
	const float defaultSpeed;
	float playerSpeed;
	int playerSpeedLevel;
	const int maxPlayerSpeedLevel;
	bool canPurchaseUpgrade;
	std::vector<float> racingScores; //These are collected through gameplay
	int coinBalance;

	std::string notificationMessage; //Appears on the top of the screen
	float showNotifUntil; //Shows notification until time;

	//Scene object specific animation variables
	float shoeShopX, shoeShopY, shoeShopZ;
	float shoeRotation;
	float shoeYOffset;

	//Rainbow calculations
	float rainbow;

	//Interaction
	bool canInteractWithSomething;
	int completedInteractionsCount[INTERACTION_COUNT]; //Everytime you finish one interaction of any type, it'll add 1 to here.

	//Queued Message, commands to execute when message is brought up
	std::vector<Interaction*> queuedMessages;
	int currentMessage;

	bool isInteracting;

	//Total time spent in Interaction
	float interactionElapsed;

	INTERACTION_TYPE currentInteractionType;
	GEOMETRY_TYPE characterOnUI; //When interacting if there is a person talking to you

	double latestInteractionSwitch; //Use counter to only allow interaction switching every 0.5s
	bool passedInteractCooldown(); //Checks if cooldown is reached;
	void nextInteraction(); //Handles the next interaction (May end interaction if there is no more to go through0


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
	void addNewTimingScore(float time);

	//Notifications
	void sendNotification(std::string msg, double duration);

	bool runCommand(std::string cmd);
	bool buySpeedUpgrade();
	bool loadInteractions(INTERACTION_TYPE type);
	void EndInteraction();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif