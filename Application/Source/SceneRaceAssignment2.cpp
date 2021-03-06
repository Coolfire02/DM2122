#include "SceneRaceAssignment2.h"
#include "SceneAssignment2.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "LoadTGA.h"
#include <Windows.h>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

#include "shader.hpp"
#include "Utility.h"

SceneRaceAssignment2::SceneRaceAssignment2() : 
	eManager(this), 
	defaultSpeed(15.f), 
	maxPlayerSpeedLevel(10)
{
	//Scene
	sceneName = "RunningScene";

	/* initialize random seed: */
	srand(time(NULL));

	//Game
	endOfRaceZValue = -255;

	raceUnlocked = false;
	playerSpeed = defaultSpeed;
	fps = 0;
	lightEnable = true;
	hitboxEnable = false;
	showNotifUntil = 0.0;

	playerSpeedLevel = 0;
	canPurchaseUpgrade = false;
	interactionElapsed = 0.0;
	upgradeCost[0] = 20;
	upgradeCost[1] = 25;
	upgradeCost[2] = 30;
	upgradeCost[3] = 40;
	upgradeCost[4] = 50;
	upgradeCost[5] = 65;
	upgradeCost[6] = 75;
	upgradeCost[7] = 85;
	upgradeCost[8] = 100;
	upgradeCost[9] = 150;

	//Interaction
	for (int i = 0; i < INTERACTION_COUNT; i++) {
		this->completedInteractionsCount[i] = 0;
	}
	canInteractWithSomething = false;
	isInteracting = false;

	//Scene object specific animation variables

	//Shoe Shop
	shoeRotation = 0.0f;
	shoeYOffset = 0.0f;
}

SceneRaceAssignment2::~SceneRaceAssignment2()
{

}

void SceneRaceAssignment2::Init() {

	// Init VBO here
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");

	//week 7
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");

	//week 9
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	//Week 14
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	glUseProgram(m_programID);

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 80.0f / 60.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);

	MeshHandler::loadMeshes();

	player = new Sonic(this, "MainPlayer");
	player->getEntityData()->rotYMag += 180;
	player->getEntityData()->transY += 4;
	player->getEntityData()->transZ -= 55;
	pOrigin = EntityData(*player->getEntityData());
	eManager.spawnMovingEntity(player);

	Entity* eggman = new NPC(this, NPCTYPE::EGGMAN, "Eggman");
	eggman->getEntityData()->scaleX = 0.04;
	eggman->getEntityData()->scaleY = 0.04;
	eggman->getEntityData()->scaleZ = 0.04;
	eggman->getEntityData()->transX = 11;
	eggman->getEntityData()->transY = 0;
	eggman->getEntityData()->transZ = -22;
	eggman->getEntityData()->rotYMag = -27.f;
	eManager.spawnWorldEntity(eggman);

	Entity* raceInteractZone = new CustomEntity(this, new Box(new Position3D(-10, 0, 3), new Position3D(10, 1, -3)), "interaction_race");
	raceInteractZone->getEntityData()->transX = 0;
	raceInteractZone->getEntityData()->transY = 0;
	raceInteractZone->getEntityData()->transZ = -40;
	eManager.spawnWorldEntity(raceInteractZone);

	Entity* eggmanInteractZone = new CustomEntity(this, new Box(new Position3D(-5, 0, 4), new Position3D(5, 1, -4)), "interaction_eggman");
	eggmanInteractZone->getEntityData()->transX = eggman->getEntityData()->transX;
	eggmanInteractZone->getEntityData()->transY = eggman->getEntityData()->transY;
	eggmanInteractZone->getEntityData()->transZ = eggman->getEntityData()->transZ;
	eManager.spawnWorldEntity(eggmanInteractZone);

	Entity* tails = new NPC(this, NPCTYPE::TAILS, "Tails");
	tails->getEntityData()->scaleX = 0.23;
	tails->getEntityData()->scaleY = 0.23;
	tails->getEntityData()->scaleZ = 0.23;
	tails->getEntityData()->transX = 28;
	tails->getEntityData()->transY = 1.5;
	tails->getEntityData()->transZ = 0.89;
	tails->getEntityData()->rotYMag = -90.f;
	eManager.spawnWorldEntity(tails);

	Entity* tailsInteractZone = new CustomEntity(this, new Box(new Position3D(-10.5, 0, 10), new Position3D(10.5, 1, -10)), "interaction_tails");
	tailsInteractZone->getEntityData()->transX = tails->getEntityData()->transX + 2.6f;
	tailsInteractZone->getEntityData()->transY = tails->getEntityData()->transY;
	tailsInteractZone->getEntityData()->transZ = tails->getEntityData()->transZ - 0.3;
	eManager.spawnWorldEntity(tailsInteractZone);

	Entity* podium = new WorldObject(this, GEO_PODIUM_1ST, "Podium_1st");
	podium->getEntityData()->transX = 32.0f;
	podium->getEntityData()->scaleX = 6;
	podium->getEntityData()->scaleY = 3;
	podium->getEntityData()->scaleZ = 6;
	eManager.spawnWorldEntity(podium);

	Entity* shopBase = new WorldObject(this, GEO_SHOPBASE, "Shop_Base");
	shopBase->getEntityData()->transX = -30.0f;
	shopBase->getEntityData()->transZ = 33.0f;
	shopBase->getEntityData()->scaleX = 6;
	shopBase->getEntityData()->scaleY = 3;
	shopBase->getEntityData()->scaleZ = 6;
	shoeShopX = shopBase->getEntityData()->transX;
	shoeShopY = shopBase->getEntityData()->transY;
	shoeShopZ = shopBase->getEntityData()->transZ;
	eManager.spawnWorldEntity(shopBase);

	Entity* shopSpotLight = new WorldObject(this, GEO_SPOTLIGHT, "Shop_Spotlight");
	shopSpotLight->getEntityData()->transX = shoeShopX - 3;
	shopSpotLight->getEntityData()->transY = 0;
	shopSpotLight->getEntityData()->transZ = shoeShopZ + 3;
	shopSpotLight->getEntityData()->rotYMag = 135.0;
	shopSpotLight->getEntityData()->scaleX = 6;
	shopSpotLight->getEntityData()->scaleY = 6;
	shopSpotLight->getEntityData()->scaleZ = 6;
	eManager.spawnWorldEntity(shopSpotLight);

	Entity* shopInteractZone = new CustomEntity(this, new Box(new Position3D(-5, 0, 5), new Position3D(5, 1, -5)), "interaction_shop");
	shopInteractZone->getEntityData()->transX = shoeShopX;
	shopInteractZone->getEntityData()->transY = shoeShopY;
	shopInteractZone->getEntityData()->transZ = shoeShopZ;
	eManager.spawnWorldEntity(shopInteractZone);

	//Camera init(starting pos, where it looks at, up
	camera.Init(Vector3(player->getEntityData()->transX, player->getEntityData()->transY+5, player->getEntityData()->transZ+13), Vector3(player->getEntityData()->transX, player->getEntityData()->transY -1, player->getEntityData()->transZ), Vector3(0, 1, 0));

	//Light init
	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.set(0, 40, 0);
	light[0].color.set(1, 1, 1); //set to white light
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	//2nd light
	light[1].type = Light::LIGHT_SPOT;
	light[1].position.set(shopSpotLight->getEntityData()->transX, shopSpotLight->getEntityData()->transY, shopSpotLight->getEntityData()->transZ);
	light[1].color.set(0.4, 0.4, 0.8); //set to white light
	light[1].power = 3;
	light[1].kC = 1.f;
	light[1].kL = 0.1f;
	light[1].kQ = 0.01f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(shoeShopX, shoeShopY+3, shoeShopZ);

	//3rd light
	light[1].type = Light::LIGHT_SPOT;
	light[1].position.set(shoeShopX, shoeShopY, shoeShopZ);
	light[1].color.set(1.0, 0.8, 0.0); //set to white light
	light[1].power = 2;
	light[1].kC = 1.f;
	light[1].kL = 0.1f;
	light[1].kQ = 0.01f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(shoeShopX, shoeShopY + 3, shoeShopZ);

	// Make sure you pass uniform parameters after glUseProgram()
	//week7
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	//week6
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	//week7
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);

	glUniform1i(m_parameters[U_LIGHT2_TYPE], light[2].type);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1, &light[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], light[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], light[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], light[2].kQ);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], light[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], light[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], light[2].exponent);

	//Week 7 - Code to change number of lights
	glUniform1i(m_parameters[U_NUMLIGHTS], 3);

	//Practical 10a
	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT], m_parameters[U_MATERIAL_DIFFUSE], m_parameters[U_MATERIAL_SPECULAR], m_parameters[U_MATERIAL_SHININESS]);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void SceneRaceAssignment2::Update(double dt)
{
	camera.Update(dt);
	player->startAnAnimation(WALK);
	racingScore += dt;

	bool foundInteractionZone = false;

	//Keys that are used inside checks (Not reliant detection if checking for pressed inside conditions etc)
	bool ePressed = Application::IsKeyPressed('E');
	bool tPressed = Application::IsKeyPressed('T');

	std::vector<CollidedWith*> collided = eManager.preCollisionUpdate();
	for (auto& entry : collided) {
		if (entry->attacker->getType() == ENTITYTYPE::SONIC) {
			if (entry->victim->getType() == ENTITYTYPE::COIN) {
				entry->victim->setDead(true);
				coinBalance++;
			}
			else if (entry->victim->getType() == ENTITYTYPE::LIVE_NPC || entry->victim->getType() == ENTITYTYPE::WORLDOBJ) {
				entry->cancelled = true;
			}
			if (entry->victim->getType() == ENTITYTYPE::CUSTOM) {
				if (entry->victim->getName().find("interaction") != std::string::npos) {
					foundInteractionZone = true;
					if(!canInteractWithSomething)
						canInteractWithSomething = true;
					else if (passedInteractCooldown()) {
						std::string name = entry->victim->getName();
						if (ePressed) {
							if (name.compare("interaction_race") == 0) {
								if (raceUnlocked) {
									loadInteractions(RACE);
								}
								else
								{
									sendNotification("Race has not been unlocked!\nTalk to Eggman first.", 3.5);
								}
							}
							else if (name.compare("interaction_tails") == 0) {
								loadInteractions(TAILS);
							}
							else if (name.compare("interaction_eggman") == 0) {
								loadInteractions(EGGMAN);
							}
							else if (name.compare("interaction_shop") == 0) {
								loadInteractions(SHOP);
							}
						}
					}
				}
			}
		}
	}
	if (foundInteractionZone == false) {
		canInteractWithSomething = false;
	}
	eManager.collisionUpdate(dt);

	if (player->usingNewData()) { //Aka movement not cancelled
		camera.Move(player->getEntityData()->transX - player->getOldEntityData()->transX,
			player->getEntityData()->transY - player->getOldEntityData()->transY,
			player->getEntityData()->transZ - player->getOldEntityData()->transZ
			);
	}

	eManager.postCollisionUpdate();

	fps = 1 / dt;
	rainbow += dt * 0.2;
	if (rainbow > 1.0) rainbow -= 1.0;

	if (isInteracting && passedInteractCooldown()) {
		if (ePressed) {
			nextInteraction();
			
		}
		else if (canPurchaseUpgrade && tPressed) {
			buySpeedUpgrade();
		}
		latestInteractionSwitch = this->elapsed;
	}

	if (GetAsyncKeyState('1') & 0x8001) {
		glEnable(GL_CULL_FACE);
	}
	else if (GetAsyncKeyState('2') & 0x8001) {
		glDisable(GL_CULL_FACE);
	}
	else if (GetAsyncKeyState('3') & 0x8001) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if (GetAsyncKeyState('4') & 0x8001) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (Application::IsKeyPressed('9')) {
		hitboxEnable = !hitboxEnable;
	}
	if (Application::IsKeyPressed('0')) {
		lightEnable = !lightEnable;
	}

	const float BOOT_ROTATION = 30.f;
	const float BOOT_YOFFSET = 0.2f;
	//Scene object specific animation variables updates
	shoeRotation += BOOT_ROTATION * dt;
	if (shoeRotation > 360) shoeRotation -= 360;
	int num = shoeRotation / 90; //Used later
	if (num % 2 == 0) shoeYOffset += BOOT_YOFFSET * dt;
	else shoeYOffset -= BOOT_YOFFSET * dt;

	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

	Vector3 pLoc = Vector3(player->getEntityData()->transX, player->getEntityData()->transY, player->getEntityData()->transZ);
	Vector3 oldLoc = Vector3(pLoc);

	const float LSPEED = 10.0;
	if (Application::IsKeyPressed('A')) {
		pLoc.x -= (float)(playerSpeed * dt);
	}
		
	if (Application::IsKeyPressed('D')) {
		pLoc.x += (float)(playerSpeed * dt);
	}

	//Running Movement
	pLoc.z -= (float)(playerSpeed * dt);
	if (pLoc.z < endOfRaceZValue) EndRacingSession();

	// SCENE WORLD BOUNDARIES
	pLoc.x = Math::Clamp(pLoc.x, -8.5f, 8.5f);

	// START MOVEMENT, TRIGGERED NEXT FRAME IF MOVEMENT NOT CANCELLED
	player->getEntityData()->transX = pLoc.x;
	//Skip y since we want level ground
	player->getEntityData()->transZ = pLoc.z;
	

	lightPosition_cameraspace = viewStack.Top() * light[1].position;
	glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
}

void SceneRaceAssignment2::Render()
{

	glEnableVertexAttribArray(0); // 1st attribute buffer: vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer: color

	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* First Triangle
	*/

	//Safe to initialize values as identity matrix (not a zero matrix!)
	//view.SetToIdentity(); //no need camera matrix, set to origin
	//projection.SetToOrtho(-80.0, 80.0, -60.0, 60.0, -10.0, 10.0);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);

	modelStack.LoadIdentity();

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(MeshHandler::getMesh(GEO_LIGHTBALL), false);
	modelStack.PopMatrix();

	if (light[0].type == Light::LIGHT_DIRECTIONAL) {
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDir_cameraSpace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDir_cameraSpace.x);

	}
	else if (light[0].type == Light::LIGHT_SPOT) {
		Position lightPos_cameraSpace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPos_cameraSpace.x);
		Vector3 spotDir_cameraSpace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDir_cameraSpace.x);

	}
	else { //Point light
		Position lightPos_cameraSpace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPos_cameraSpace.x);
	}

	if (light[1].type == Light::LIGHT_DIRECTIONAL) {
		Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
		Vector3 lightDir_cameraSpace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDir_cameraSpace.x);

	}
	else if (light[1].type == Light::LIGHT_SPOT) {
		Position lightPos_cameraSpace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPos_cameraSpace.x);
		Vector3 spotDir_cameraSpace = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDir_cameraSpace.x);

	}
	else { //Point light
		Position lightPos_cameraSpace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPos_cameraSpace.x);
	}

	this->RenderSkybox();

	//WORLD
	modelStack.PushMatrix();
		modelStack.Translate(0.0f, -50.0f, 0.0f);
		modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(50.f, 50.f, 50.f);
		this->RenderMesh(MeshHandler::getMesh(GEO_OBJ_GRASS), lightEnable);

	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(100.0f, -40.0f, 0.0f);
		modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(50.f, 50.f, 50.f);
		this->RenderMesh(MeshHandler::getMesh(GEO_OBJ_GRASS), lightEnable);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-100.0f, -40.0f, 0.0f);
		modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(50.f, 50.f, 50.f);
		this->RenderMesh(MeshHandler::getMesh(GEO_OBJ_GRASS), lightEnable);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(0.0f, -40.0f, 100.0f);
		modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(50.f, 50.f, 50.f);
		this->RenderMesh(MeshHandler::getMesh(GEO_OBJ_GRASS), lightEnable);
	modelStack.PopMatrix();

	for (int i = 1; i <= 3; i++) {
		modelStack.PushMatrix();
		modelStack.Translate(60.0f, -35.0f, -100.0f * i);
		modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(50.f, 50.f, 50.f);
		this->RenderMesh(MeshHandler::getMesh(GEO_OBJ_GRASS), lightEnable);
		modelStack.PopMatrix();
	}

	for (int i = 1; i <= 3; i++) {
		modelStack.PushMatrix();
			modelStack.Translate(-60.0f, -35.0f, -100.0f*i);
			modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(50.f, 50.f, 50.f);
			this->RenderMesh(MeshHandler::getMesh(GEO_OBJ_GRASS), lightEnable);
		modelStack.PopMatrix();
	}

	//End Race
	modelStack.PushMatrix();
		modelStack.Translate(0.0f, -35.0f, -320.0f);
		modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(50.f, 50.f, 50.f);
		this->RenderMesh(MeshHandler::getMesh(GEO_OBJ_GRASS), lightEnable);
	modelStack.PopMatrix();



	modelStack.PushMatrix();
		modelStack.Translate(0.0f, 0.f, -100.0f);
		modelStack.Rotate(-90, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(20.f, 100.f, 1.f);
		this->RenderMesh(MeshHandler::getMesh(GEO_RUNNINGFLOOR), lightEnable);
		
		modelStack.PushMatrix();
			modelStack.Translate(0.0f, 1.f, 0.0f);
			modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(1.f, 1.f, 1.f);
			this->RenderMesh(MeshHandler::getMesh(GEO_RUNNINGFLOOR), lightEnable);

			modelStack.PushMatrix();
				modelStack.Translate(0.0f, 0.622f, 0.0f);
				modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
				modelStack.Scale(1.f, 0.6f, 1.f);
				this->RenderMesh(MeshHandler::getMesh(GEO_ENDRACE), lightEnable);
			modelStack.PopMatrix();
		modelStack.PopMatrix();
	modelStack.PopMatrix();


	for (auto& entity : eManager.getEntities()) {
		entity->Render();
		if (hitboxEnable) { //Downside: Can't view hitbox accurately of Objects that are rotated
			modelStack.PushMatrix();
			Mesh* mesh = MeshBuilder::GenerateHitBox("hitbox", entity->getHitBox()->getThisTickBox()->botLeftPos, entity->getHitBox()->getThisTickBox()->topRightPos);
			this->RenderMesh(mesh, lightEnable);
			modelStack.PopMatrix();
			delete mesh;
		}
	}

	//Sonic Shop Shoe Display

	this->modelStack.PushMatrix();
		
		this->modelStack.Translate(shoeShopX, shoeShopY + 4.0f + shoeYOffset, shoeShopZ);
		this->modelStack.Rotate(shoeRotation, 0.0f, 1.0f, 0.f);
		this->modelStack.Scale(0.14f, 0.14f, 0.14f);
		//Right Shoe

		//Front shoe
		this->modelStack.PushMatrix();
			this->modelStack.Translate(8.4f * RIGHT, -8.0f, 0.0f);
			this->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
			this->modelStack.Scale(5.0f, 8.f, 10.f);
			this->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BOOTSQUATERSPHERE), true);

			//Lace
			this->modelStack.PushMatrix();
				this->modelStack.Rotate(90, 0.0f, 1.0f, 0.0f);
				this->modelStack.Translate(-0.3f, 0.0f, 0.0f);
				this->modelStack.Rotate(-83, 0.0f, 0.0f, 1.0f);
				this->modelStack.Scale(0.75f, 4.f, 0.8f); //x is tallness, y value is width, 
				this->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BOOTSLACEHALFTORUS), true);

			this->modelStack.PopMatrix();

			this->modelStack.PushMatrix();
				this->modelStack.Translate(0.f, -0.12f, 0.25f);
				this->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
				this->modelStack.Scale(0.8f, 0.8f, 0.6f);
				this->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BOOTSFEETTORUS), true);
			this->modelStack.PopMatrix();

		this->modelStack.PopMatrix();

		//Back shoe
		this->modelStack.PushMatrix();
			this->modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
			this->modelStack.Translate(-8.4f * RIGHT, -8.0f, -0.3f);
			this->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
			this->modelStack.Scale(5.0f, 8.f, 4.f);
			this->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BOOTSQUATERSPHERE), true);

		this->modelStack.PopMatrix();

		//Left Shoe
		//Front shoe
		this->modelStack.PushMatrix();
			this->modelStack.Translate(8.4f * LEFT, -8.0f, 0.0f);
			this->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
			this->modelStack.Scale(5.0f, 8.f, 10.f);
			this->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BOOTSQUATERSPHERE), true);

			//Lace
			this->modelStack.PushMatrix();
				this->modelStack.Rotate(90, 0.0f, 1.0f, 0.0f);
				this->modelStack.Translate(-0.3f, 0.0f, 0.0f);
				this->modelStack.Rotate(-83, 0.0f, 0.0f, 1.0f);
				this->modelStack.Scale(0.75f, 4.f, 0.8f); //x is tallness, y value is width, 
				this->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BOOTSLACEHALFTORUS), true);

			this->modelStack.PopMatrix();

			this->modelStack.PushMatrix();
				this->modelStack.Translate(0.f, -0.12f, 0.25f);
				this->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
				this->modelStack.Scale(0.8f, 0.8f, 0.6f);
				this->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BOOTSFEETTORUS), true);
			this->modelStack.PopMatrix();

		this->modelStack.PopMatrix();

		//Back shoe
		this->modelStack.PushMatrix();
			this->modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
			this->modelStack.Translate(-8.4f * LEFT, -8.0f, -0.3f);
			this->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
			this->modelStack.Scale(5.0f, 8.f, 4.f);
			this->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BOOTSQUATERSPHERE), true);

		this->modelStack.PopMatrix();

	this->modelStack.PopMatrix();

	std::ostringstream ss;

	//World Text
	modelStack.PushMatrix();
		modelStack.Translate(shoeShopX+3, shoeShopY+10, shoeShopZ+3);
		modelStack.Rotate(135, 0.0f, 1.0f, 0.0f);
		modelStack.Scale(1.0f, 1.0f, 1.0f);
		this->RenderText(MeshHandler::getMesh(GEO_TEXT), "Speed Upgrade Shop", Color(0.9, 0.7, 0.01));
		
		modelStack.PushMatrix();
			modelStack.Translate(0.2, -1, 0.2);
			modelStack.Rotate(0, 0.0f, 1.0f, 0.0f);
			modelStack.Scale(1.0f, 1.0f, 1.0f);
			ss << "Level ("<< playerSpeedLevel <<"/"<<maxPlayerSpeedLevel<<"): " << std::setprecision(2) << playerSpeed/defaultSpeed << "x Speed";
			this->RenderText(MeshHandler::getMesh(GEO_TEXT), ss.str(), Color(0.9, 0.7, 0.01));


		modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-3.0, 8, -50.0);
		modelStack.Rotate(0, 0.0f, 1.0f, 0.0f);
		modelStack.Scale(3.0f, 3.0f, 3.0f);
		ss.str("");
		ss.clear();
		ss << "RUNNER";
		this->RenderText(MeshHandler::getMesh(GEO_TEXT), ss.str(), Color(1.0 - rainbow * 0.5, pow(rainbow,0.5), rainbow));

		modelStack.PushMatrix();
			modelStack.Translate(-1.0, -0.42, 0.0);
			modelStack.Rotate(0, 0.0f, 1.0f, 0.0f);
			modelStack.Scale(0.5f, 0.5f, 0.5f);
			ss.str("");
			ss.clear();
			ss << "Interact to Start";
			this->RenderText(MeshHandler::getMesh(GEO_TEXT), ss.str(), Color(0.9, 0.8, 0.0));

		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(-0.1, -1.04, 0.0);
			modelStack.Rotate(0, 0.0f, 1.0f, 0.0f);
			modelStack.Scale(0.33f, 0.33f, 0.33f);
			ss.str("");
			ss.clear();
			ss << "PBest Time: " << getRacingTime();
			this->RenderText(MeshHandler::getMesh(GEO_TEXT), ss.str(), Color(0.4, 1.0, 1.0));
		modelStack.PopMatrix();

	modelStack.PopMatrix();

	//UI Text

	//Interaction UI
	if (isInteracting) {
		Interaction* inter = queuedMessages.at(currentMessage);
		std::vector<std::string> splitVar;
		split(inter->interactionText, '\n', splitVar);
		const double offset = 2.5;
		int i = 0;
		int additionalYSize = splitVar.size() - 3;
		if (additionalYSize > 0) {
			additionalYSize = 10 * additionalYSize;
		}
		else {
			additionalYSize = 0;
		}
		//Calculate text offset
		const double textYStart = 10.5+(additionalYSize/10+1)*offset;
		//Renders backdrop
		RenderMeshOnScreen(MeshHandler::getMesh(GEO_TEXTBACKDROP), 40, 10, 73, 40+additionalYSize);
		//Renders text;
		for (auto& entry : splitVar) {
			ss.str("");
			ss.clear();
			ss << entry;
			RenderTextOnScreen(MeshHandler::getMesh(GEO_TEXT), ss.str(), Color(0.8, 0.6, 1.0), 3.5, 7, textYStart-offset*i);
			i++;
		}
		//Renders Press E to close
		ss.str("");
		ss.clear();
		ss << "Press E to " << (currentMessage+1 == queuedMessages.size() ? "Close" : "Continue");
		RenderTextOnScreen(MeshHandler::getMesh(GEO_TEXT), ss.str(), Color(0.8, 0.6, 1.0), 3.5, 40, textYStart - offset * (++i < 4? 4: i));
	}

	//Notification UI
	if (showNotifUntil > elapsed) {

		std::vector<std::string> splitVar;
		split(notificationMessage, '\n', splitVar);
		const double offset = 3.0;
		int i = 0;
		for (auto& entry : splitVar) {
			ss.str("");
			ss.clear();
			ss << entry;
			RenderTextOnScreen(MeshHandler::getMesh(GEO_TEXT), ss.str(), Color(0.1, 0.4, 0.1), 4, 10, 20-offset*i);
			i++;
		}

	}

	//Coins UI
	RenderMeshOnScreen(MeshHandler::getMesh(GEO_COINS_METER), 9, 55, 15, 13);
	
	ss.str("");
	ss.clear();
	std::string bal = std::to_string(coinBalance);
	if (coinBalance < 10) bal = "0" + bal;
	if (coinBalance < 100) bal = "0" + bal;
	if (coinBalance > 999) bal = "999";
	ss << bal;
	RenderTextOnScreen(MeshHandler::getMesh(GEO_TEXT), ss.str(), Color(0, 0, 0), 5, 7, 52.5);

	//Time UI
	RenderMeshOnScreen(MeshHandler::getMesh(GEO_TIME_METER), 9, 49, 15, 13);
	RenderTextOnScreen(MeshHandler::getMesh(GEO_TEXT), getRacingTime(), Color(0, 0, 0), 4, 7, 46.5);
	RenderTextOnScreen(MeshHandler::getMesh(GEO_TEXT), getRacingTimeMilliCounter(), Color(0, 0, 0), 2, 12, 49.5);

	//Interaction MSG UI
	if (canInteractWithSomething && !isInteracting) {
		ss.str("");
		ss.clear();
		ss << "Press 'E' to Interact";
		RenderTextOnScreen(MeshHandler::getMesh(GEO_TEXT), ss.str(), Color(1, 1, 1), 4, 20, 10);
	}
	
	//FPS UI
	ss.str("");
	ss.clear();
	ss << "FPS: " << fps;
	RenderTextOnScreen(MeshHandler::getMesh(GEO_TEXT), ss.str(), Color(0, 1, 0), 4, 0, 5);
}

void SceneRaceAssignment2::StartRacingSession() {
	genCoins();
	int XDiff = pOrigin.transX - player->getEntityData()->transX;
	int YDiff = pOrigin.transY - player->getEntityData()->transY;
	int ZDiff = pOrigin.transZ -player->getEntityData()->transZ;
	camera.Move(XDiff, YDiff, ZDiff);

	player->getEntityData()->transX = pOrigin.transX;
	player->getEntityData()->transY = pOrigin.transY;
	player->getEntityData()->transZ = pOrigin.transZ;
	player->PostUpdate(); //Make OldData back to origin
}

void SceneRaceAssignment2::setPlayerSpeed(float speed) {
	this->playerSpeed = speed;
}

void SceneRaceAssignment2::genCoins() {
	for (int i = 0; i < 20; i++) {
		Mesh* coinMesh = MeshHandler::getMesh(GEOMETRY_TYPE::GEO_COIN);
		Entity* newCoin = new Coin(this, new Box(new Position3D(coinMesh->botLeftPos), new Position3D(coinMesh->topRightPos)), "Coin");
		newCoin->getEntityData()->rotXMag = 90.f;
		newCoin->getEntityData()->transX = (rand() % 3 - 1) * 2.8;
		newCoin->getEntityData()->transY = 1.6;
		newCoin->getEntityData()->transZ = -55 - i * 12;
		newCoin->getEntityData()->scaleX = 0.3;
		newCoin->getEntityData()->scaleY = 0.3;
		newCoin->getEntityData()->scaleZ = 0.3;
		eManager.spawnWorldEntity(newCoin);
	}
}

void SceneRaceAssignment2::EndRacingSession() {
	Scene* mainScene = Application::getSceneByName("MainScene");
	(static_cast<SceneAssignment2*>(mainScene))->addCoins(coinBalance);
	(static_cast<SceneAssignment2*>(mainScene))->addNewTimingScore(racingScore);
	for (auto& entry : eManager.getEntities()) {
		if (entry->getType() == ENTITYTYPE::COIN) {
			entry->setDead(true);
		}
	}
	coinBalance = 0;
	racingScore = 0;
	Application::changeToScene("MainScene", "");
}

std::string SceneRaceAssignment2::getRacingTime() {
	int min = racingScore / 60;
	int sec = racingScore - min * 60;
	std::string str = std::to_string(min) + ":" + (sec < 10 ? "0" : "") + std::to_string(sec);
	return str;
}

std::string SceneRaceAssignment2::getRacingTimeMilliCounter() {
	int millis = (racingScore - (int) racingScore) * 1000.0;
	if (millis > 999) millis = 999;
	std::string str = std::to_string(millis);
	if (millis < 10) str = "0" + str;
	if (millis < 100) str = "0" + str;
	return str;
}

void SceneRaceAssignment2::RenderSkybox() {
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
		modelStack.PushMatrix();
		modelStack.Translate(-250.0f, 0.0f, 0.0f);
		modelStack.Rotate(90, 0.0f, 1.0f, 0.0f);
		modelStack.Scale(500.0f, 500.0f, 500.0f);
		this->RenderMesh(MeshHandler::getMesh(GEO_SKY_LEFT), false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(250.0f, 0.0f, 0.0f);
		modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f);
		modelStack.Scale(500.0f, 500.0f, 500.0f);
		this->RenderMesh(MeshHandler::getMesh(GEO_SKY_RIGHT), false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0.0f, 250.0f, 0.0f);
		modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f);
		modelStack.Rotate(90, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(500.0f, 500.0f, 500.0f);
		this->RenderMesh(MeshHandler::getMesh(GEO_SKY_TOP), false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0.0f, -250.0f, 0.0f);
		modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f);
		modelStack.Rotate(90, -1.0f, 0.0f, 0.0f);
		modelStack.Scale(500.0f, 500.0f, 500.0f);
		this->RenderMesh(MeshHandler::getMesh(GEO_SKY_BOTTOM), false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0.0f, 0.0f, -250.0f);
		modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(500.0f, 500.0f, 500.0f);
		this->RenderMesh(MeshHandler::getMesh(GEO_SKY_BACK), false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0.0f, 0.0f, 250.0f);
		modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
		modelStack.Scale(500.0f, 500.0f, 500.0f);
		this->RenderMesh(MeshHandler::getMesh(GEO_SKY_FRONT), false);
		modelStack.PopMatrix();

	modelStack.PopMatrix();
}

bool SceneRaceAssignment2::passedInteractCooldown() {
	const float INTERACTION_COOLDOWN = 0.5f;
	if (latestInteractionSwitch + INTERACTION_COOLDOWN < this->elapsed) {
		return true;
	}
	return false;
}

int SceneRaceAssignment2::getCoins() {
	return coinBalance;
}

void SceneRaceAssignment2::setCoins(int val) {
	coinBalance = val;
}

void SceneRaceAssignment2::addCoins(int val) {
	coinBalance += val;
}

void SceneRaceAssignment2::sendNotification(std::string msg, double duration) {
	showNotifUntil = elapsed + duration;
	notificationMessage = msg;
}

void SceneRaceAssignment2::split(std::string txt, char delim, std::vector<std::string>& out) {
	std::istringstream iss(txt);
	std::string item;
	while (std::getline(iss, item, delim)) {
		out.push_back(item);
	}
}

bool SceneRaceAssignment2::runCommand(std::string cmd) {
	std::vector<std::string> splitVar;
	split(cmd, ' ', splitVar);

	if (splitVar.size() == 1) {
		if (splitVar.at(0) ==  "/startrace") {
			//Start race code todo
			return true;
		}
		else if (splitVar.at(0) == "/endinteraction") {
			queuedMessages.clear();
			//End Interaction todo
			return true;
		}
		else if (splitVar.at(0) == "/unlockrace") {
			raceUnlocked = true;
			sendNotification("Race has been UNLOCKED", 5.0);
			//End Interaction todo
			return true;
		}
		else if (splitVar.at(0) == "/buyupgrade") {
			//Upgrade todo
			return true;
		}
		else if (splitVar.at(0) == "/enablebootupgrades") {
			canPurchaseUpgrade = true;
			return true;
		}
		else if (splitVar.at(0) == "/disablebootupgrades") {
			canPurchaseUpgrade = false;
			return true;
		}
	}
	else if (splitVar.size() >= 2) {
		if (splitVar.at(0) == "/givecoin") {
			this->addCoins(stoi(splitVar.at(1)));
			return true;
		}
	}

	return true;
}

bool SceneRaceAssignment2::buySpeedUpgrade() {
	if (playerSpeedLevel < maxPlayerSpeedLevel) {
		if (coinBalance > upgradeCost[this->playerSpeedLevel]) {
			coinBalance -= upgradeCost[this->playerSpeedLevel];
			playerSpeedLevel++;
			playerSpeed = defaultSpeed * (1 + 0.05 * playerSpeedLevel);
			sendNotification("Purchase successful", 4.5);
		}
		else {
			sendNotification("You need " +std::to_string(upgradeCost[this->playerSpeedLevel])+" Coins to Upgrade!", 3.0);
		}
	}
	else {
		sendNotification("Already Maxed!", 3.0);
	}
	return false;
}

bool SceneRaceAssignment2::loadInteractions(INTERACTION_TYPE type) {
	if (!isInteracting) {

		switch (type) {
		case TAILS:
		{
			Interaction* inter;
			if (completedInteractionsCount[TAILS] == 0) {
				inter = new Interaction();
				inter->interactionText = "Hey There!";
				queuedMessages.push_back(inter);
				
				inter = new Interaction();
				inter->interactionText = "It's been a while since\nI've found a new potential\ncompetitor...";
				queuedMessages.push_back(inter);
				if (completedInteractionsCount[EGGMAN] > 0) {
					inter = new Interaction();
					inter->interactionText = "Don't worry about Eggman\nHe's such a sob. Could\nnever beat me";
					queuedMessages.push_back(inter);

					inter = new Interaction();
					inter->interactionText = "Explains why he's mad\nas he sees potential in you.";
					queuedMessages.push_back(inter);
				}
			}
			else {
				inter = new Interaction();
				inter->interactionText = "Hey there again!";
				queuedMessages.push_back(inter);
			}
			inter = new Interaction();
			inter->interactionText = "Oh, you wanna know my\nTiming for the race?";
			queuedMessages.push_back(inter);

			inter = new Interaction();
			inter->interactionText = "I ran and completed it in...\n";
			queuedMessages.push_back(inter);

			inter = new Interaction();
			inter->interactionText = "0 minutes and 8 seconds!";
			queuedMessages.push_back(inter);



			break;
		}
		case EGGMAN:
		{
			Interaction* inter;
			if (completedInteractionsCount[EGGMAN] == 0) {

				inter = new Interaction();
				inter->interactionText = "So... You're new around here?";
				queuedMessages.push_back(inter);

				inter = new Interaction();
				inter->interactionText = "HAHAHA, You'll Never Beat\nanyone here, look at your speed";
				queuedMessages.push_back(inter);

				inter = new Interaction();
				inter->interactionText = "Well anyways, I hope you f..\nI mean succeed!";
				inter->preInteractionCMD.push_back("/unlockrace");
				queuedMessages.push_back(inter);
			}
			else {
				switch (playerSpeedLevel) {
				case 1:
					inter = new Interaction();
					inter->interactionText = "So your back again!";
					queuedMessages.push_back(inter);

					inter = new Interaction();
					inter->interactionText = "Couldn't beat Tails huh,\nof course you couldnt!";
					queuedMessages.push_back(inter);

					if (completedInteractionsCount[EGGMAN] == 1) {
						inter = new Interaction();
						inter->interactionText = "Go back to the dumpster!\nHere's 10 pitty coins";
						inter->postInteractionCMD.push_back("/givecoin 10");
						queuedMessages.push_back(inter);
					}
					break;

				case 3:
					inter = new Interaction();
					inter->interactionText = "Dangg, you're catching up...";
					queuedMessages.push_back(inter);

					inter = new Interaction();
					inter->interactionText = "Maybe if I waited long enough...\nan 'I CARE' could fall\nfrom the Sky!";
					queuedMessages.push_back(inter);
					break;

				default:
					inter = new Interaction();
					inter->interactionText = "Loser!!!";
					queuedMessages.push_back(inter);
				}
			}

			break;
		}

			break;
		case SHOP:
		{
			Interaction* inter;
			if (completedInteractionsCount[SHOP] == 0) {

				inter = new Interaction();
				inter->interactionText = "Welcome to the Shop!\nHere you can purchase Speed Upgrades\nto get you going faster in races!";
				queuedMessages.push_back(inter);

				inter = new Interaction();
				inter->preInteractionCMD.push_back("/givecoin 1");
				inter->interactionText = "Here's a free first coin.";
				queuedMessages.push_back(inter);
			}

			inter = new Interaction();
			inter->preInteractionCMD.push_back("/enablebootupgrades");
			inter->interactionText = "Purchase Upgrades here.\nPress 'T' to Purchase an Upgrade.";
			inter->postInteractionCMD.push_back("/disablebootupgrades");
			queuedMessages.push_back(inter);
			break;
		}
		case RACE:
			break;
		default:
			return false;
		}

		currentInteractionType = type;
		interactionElapsed = 0;
		latestInteractionSwitch = this->elapsed;
		isInteracting = true;
		currentMessage = -1; //Used to call first Interaction's precmds too. by Using nextInteraction();
		nextInteraction();

		return true;
	}
	return false;
}

void SceneRaceAssignment2::nextInteraction() {
	if (currentMessage > 0) { //Post Interaction CMDs to execute (Interaction prior to the one being moved to now)
		for (auto& entry : queuedMessages.at(currentMessage)->postInteractionCMD) {
			this->runCommand(entry);
		}
	}
	currentMessage += 1;
	if (queuedMessages.size() < currentMessage + 1) {
		EndInteraction();
	}
	else {
		for (auto& entry : queuedMessages.at(currentMessage)->preInteractionCMD) { //Pre Interaction CMDs to execute
			this->runCommand(entry);
		}
	}
}

void SceneRaceAssignment2::EndInteraction() {
	if (isInteracting) {

		completedInteractionsCount[currentInteractionType]++;

		isInteracting = false;
		currentMessage = 0;
		for (auto& entry : queuedMessages) { //clears all pointers
			delete entry;
		}
		queuedMessages.clear();
		interactionElapsed = 0;
		currentInteractionType = INTERACTION_COUNT;
	}
}

void SceneRaceAssignment2::Exit()
{
	// Cleanup VBO here
	this->EndInteraction(); //To clear up queuedMessages pointers

	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}