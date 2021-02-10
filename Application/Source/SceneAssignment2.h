#ifndef SCENE_ASSIGNMENT2_H
#define SCENE_ASSIGNMENT2_H

#include <map>

#include "Scene.h"
#include "FirstPersonCamera.h"	
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Interactions.h"

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

private:

	FirstPersonCamera camera;
	EntityManager eManager;
	Entity* player;

	//Game
	bool raceUnlocked;

	//Shop
	int upgradeCost[10];
	const float defaultSpeed;
	float playerSpeed;
	int playerSpeedLevel;
	const int maxPlayerSpeedLevel;
	bool canPurchaseUpgrade;
	int coinBalance;

	//Racing
	std::string getRacingTime(int index); //Index represents location in RacingScores vector
	std::string getRacingTimeMilliCounter(int index);
	std::vector<float> racingScores; //These are collected through gameplay

	//Notification Channel
	std::string notificationMessage; //Appears on the top of the screen
	float showNotifUntil; //Shows notification until time;

	//Scene object specific animation variables
	float shoeShopX, shoeShopY, shoeShopZ;
	float shoeRotation;
	float shoeYOffset;

	//Rainbow calculations
	float rainbow;

	//Interaction
	bool isInteracting;
	float interactionElapsed; //Total time spent in Interaction instance
	bool canInteractWithSomething;
	int completedInteractionsCount[INTERACTION_COUNT]; //Everytime you finish one interaction of any type, it'll add 1 to here.

	//Queued Message, commands to execute when message is brought up
	std::vector<Interaction*> queuedMessages;
	int currentMessage;

	INTERACTION_TYPE currentInteractionType;
	GEOMETRY_TYPE characterOnUI; //When interacting if there is a person talking to you

	double latestInteractionSwitch; //Use counter to only allow interaction switching every 0.5s
	bool passedInteractCooldown(); //Checks if cooldown is reached;
	void nextInteraction(); //Handles the next interaction (May end interaction if there is no more to go through0
	
	//@Deprecated, Moved over to MeshHandler
	Mesh* meshList[NUM_GEOMETRY];
	Light light[3];

	bool hitboxEnable;
	float fps;
	
	void RenderSkybox();
	void split(std::string txt, char delim, std::vector<std::string>& out);

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