#include "SceneAssignment2.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "LoadTGA.h"
#include <Windows.h>
#include <algorithm>
#include <sstream>
#include <iomanip>

#include "shader.hpp"
#include "Utility.h"



SceneAssignment2::SceneAssignment2() : 
	eManager(this), 
	defaultSpeed(15.f), 
	maxPlayerSpeedLevel(10)
{
	//Scene
	sceneName = "MainScene";

	//Game
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

SceneAssignment2::~SceneAssignment2()
{

}

void SceneAssignment2::Init() {

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
	player->getEntityData()->transY += 4;
	player->setVisibility(false);
	eManager.spawnMovingEntity(player);



	Mesh* coinMesh = MeshHandler::getMesh(GEOMETRY_TYPE::GEO_COIN);
	Entity* newCoin = new Coin(this, new Box(coinMesh->botLeftPos, coinMesh->topRightPos), "Coin");
	newCoin->getEntityData()->rotXMag = 90.f;
	newCoin->getEntityData()->transX = 8.0;
	newCoin->getEntityData()->transY = 1.3;
	newCoin->getEntityData()->scaleX = 0.2;
	newCoin->getEntityData()->scaleY = 0.2;
	newCoin->getEntityData()->scaleZ = 0.2;
	eManager.spawnWorldEntity(newCoin);

	for (int i = 0; i < 10; i++) {
		coinMesh = MeshHandler::getMesh(GEOMETRY_TYPE::GEO_COIN);
		newCoin = new Coin(this, new Box(coinMesh->botLeftPos, coinMesh->topRightPos), "Coin");
		newCoin->getEntityData()->rotXMag = 90.f;
		newCoin->getEntityData()->transX = 0.0;
		newCoin->getEntityData()->transY = 1.6;
		newCoin->getEntityData()->transZ = -55 - i * 5;
		newCoin->getEntityData()->scaleX = 0.3;
		newCoin->getEntityData()->scaleY = 0.3;
		newCoin->getEntityData()->scaleZ = 0.3;
		eManager.spawnWorldEntity(newCoin);
	}

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
	camera.Init(Vector3(player->getEntityData()->transX, player->getEntityData()->transY+2, player->getEntityData()->transZ), Vector3(0, 0, 1), Vector3(0, 1, 0));

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


	//Universal material template used for testing
	Material mat;
	mat.kAmbient.Set(0.1f, 0.1f, 0.1f);
	mat.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	mat.kSpecular.Set(0.3f, 0.3f, 0.3f);
	mat.kShininess = 1.0f;

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes", 1, 1, 1);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightbulll", Color(1.0f, 1.0f, 1.0f));


	///*meshList[GEO_OBJ_ISLAND] = MeshBuilder::GenerateOBJ("island", "OBJ//island.obj");
	//meshList[GEO_OBJ_ISLAND]->textureID = LoadTGA("Image//island.tga");*/

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");



	//Platform
	meshList[GEO_OBJ_FENCE] = MeshBuilder::GenerateOBJMTL("fence", "OBJ//fence2.obj", "MTL//fence.mtl");
	meshList[GEO_OBJ_FENCE]->textureID = LoadTGA("Image//fence.tga");

	meshList[GEO_OBJ_GRASS] = MeshBuilder::GenerateOBJMTL("grass", "OBJ//blockLarge.obj", "MTL//blockLarge.mtl");

	//UI
	meshList[GEO_COINS_METER] = MeshBuilder::GenerateQuad("coin", Color(1, 1, 1));
	meshList[GEO_COINS_METER]->textureID = LoadTGA("Image//coin.tga");

	meshList[GEO_TIME_METER] = MeshBuilder::GenerateQuad("timer", Color(1, 1, 1));
	meshList[GEO_TIME_METER]->textureID = LoadTGA("Image//time.tga");

	//Skybox Meshes
	meshList[GEO_SKY_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1));
	meshList[GEO_SKY_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1));
	meshList[GEO_SKY_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1));
	meshList[GEO_SKY_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1));
	meshList[GEO_SKY_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1));
	meshList[GEO_SKY_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1));
	meshList[GEO_ICON] = MeshBuilder::GenerateQuad("icon", Color(1, 1, 1));

	meshList[GEO_SKY_LEFT]->textureID = LoadTGA("Image//bluecloud_lf.tga");
	meshList[GEO_SKY_RIGHT]->textureID = LoadTGA("Image//bluecloud_rt.tga");
	meshList[GEO_SKY_TOP]->textureID = LoadTGA("Image//bluecloud_up.tga");
	meshList[GEO_SKY_BOTTOM]->textureID = LoadTGA("Image//bluecloud_dn.tga");
	meshList[GEO_SKY_FRONT]->textureID = LoadTGA("Image//bluecloud_ft.tga");
	meshList[GEO_SKY_BACK]->textureID = LoadTGA("Image//bluecloud_bk.tga");
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void SceneAssignment2::Update(double dt)
{
	camera.Update(dt);

	bool foundInteractionZone = false;

	//Keys that are used inside checks (Not reliant detection if checking for pressed inside conditions etc)
	bool ePressed = Application::IsKeyPressed('E');
	bool tPressed = Application::IsKeyPressed('T');

	std::vector<CollidedWith*> collided = eManager.preCollisionUpdate();
	for (auto& entry : collided) {
		if (entry->attacker->getType() == ENTITYTYPE::SONIC) {
			if (entry->victim->getType() == ENTITYTYPE::LIVE_NPC || entry->victim->getType() == ENTITYTYPE::WORLDOBJ) {
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
			player->getEntityData()->transZ - player->getOldEntityData()->transZ);
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

	//if (Application::IsKeyPressed('5')) {
	//	//to do: switch light type to POINT and pass the information to shader
	//	light[0].type = Light::LIGHT_POINT;
	//	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	//}
	//else if (Application::IsKeyPressed('6')) {
	//	//to do: switch light type to DIRECTIONAL and pass the information to shader
	//	light[0].type = Light::LIGHT_DIRECTIONAL;
	//	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	//}
	//else if (Application::IsKeyPressed('7')) {
	//	//to do: switch light type to SPOT and pass the information to shader
	//	light[0].type = Light::LIGHT_SPOT;
	//	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	//}
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


	//const float LSPEED = 10.f;
	//if (Application::IsKeyPressed('I'))
	//	light[0].position.z -= (float)(LSPEED * dt);
	//if (Application::IsKeyPressed('K'))
	//	light[0].position.z += (float)(LSPEED * dt);
	//if (Application::IsKeyPressed('J'))
	//	light[0].position.x -= (float)(LSPEED * dt);
	//if (Application::IsKeyPressed('L'))
	//	light[0].position.x += (float)(LSPEED * dt);
	//if (Application::IsKeyPressed('O'))
	//	light[0].position.y -= (float)(LSPEED * dt);
	//if (Application::IsKeyPressed('P'))
	//	light[0].position.y += (float)(LSPEED * dt);
	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

	Vector3 pLoc = Vector3(player->getEntityData()->transX, player->getEntityData()->transY, player->getEntityData()->transZ);
	Vector3 oldLoc = Vector3(pLoc);

	if (Application::IsKeyPressed('W')) {
		Vector3 view = (camera.target - camera.position).Normalized();
		pLoc += view * (float)dt *  playerSpeed;
		//player->getEntityData()->transZ -= (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('A')) {
		Vector3 view = (camera.target - camera.position).Normalized();
		Vector3 right = view.Cross(camera.up);
		right.y = 0;
		right.Normalize();
		Vector3 up = right.Cross(view).Normalized();
		pLoc -= right * (float)dt * playerSpeed;
		//player->getEntityData()->transX -= (float)(LSPEED * dt);
	}
		
	if (Application::IsKeyPressed('S')) {
		Vector3 view = (camera.target - camera.position).Normalized();
		pLoc -= view * (float)dt * playerSpeed;
		//player->getEntityData()->transZ += (float)(LSPEED * dt);
	}
		
	if (Application::IsKeyPressed('D')) {
		Vector3 view = (camera.target - camera.position).Normalized();
		Vector3 right = view.Cross(camera.up);
		right.y = 0;
		right.Normalize();
		Vector3 up = right.Cross(view).Normalized();
		pLoc += right * (float)dt * playerSpeed;
		//player->getEntityData()->transX += (float)(LSPEED * dt);
	}
	

	// SCENE WORLD BOUNDARIES
	pLoc.x = Math::Clamp(pLoc.x, -40.f, 40.f);
	pLoc.z = Math::Clamp(pLoc.z, -40.f, 40.f);

	// START MOVEMENT, TRIGGERED NEXT FRAME IF MOVEMENT NOT CANCELLED
	player->getEntityData()->transX = pLoc.x;
	//Skip y since we want level ground
	player->getEntityData()->transZ = pLoc.z;
	

	lightPosition_cameraspace = viewStack.Top() * light[1].position;
	glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
}

void SceneAssignment2::Render()
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
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
	modelStack.Scale(1, 1, 1);
	this->RenderMesh(meshList[GEO_AXES], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	//modelStack.PushMatrix(); //pushing identity
	//	modelStack.Translate(0.0f, 0.0f, 0.0f);
	//	modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
	//	modelStack.Scale(3.0f, 1.8f, 1.0f);
	//	this->RenderMesh(meshList[GEO_CUBE], true);
	//modelStack.PopMatrix();

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
		this->RenderMesh(meshList[GEO_OBJ_GRASS], lightEnable);	

	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(100.0f, -40.0f, 0.0f);
		modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(50.f, 50.f, 50.f);
		this->RenderMesh(meshList[GEO_OBJ_GRASS], lightEnable);	
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-100.0f, -40.0f, 0.0f);
		modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(50.f, 50.f, 50.f);
		this->RenderMesh(meshList[GEO_OBJ_GRASS], lightEnable);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(0.0f, -40.0f, 100.0f);
		modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(50.f, 50.f, 50.f);
		this->RenderMesh(meshList[GEO_OBJ_GRASS], lightEnable);	
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(60.0f, -35.0f, -100.0f);
		modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(50.f, 50.f, 50.f);
		this->RenderMesh(meshList[GEO_OBJ_GRASS], lightEnable);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-60.0f, -35.0f, -100.0f);
		modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(50.f, 50.f, 50.f);
		this->RenderMesh(meshList[GEO_OBJ_GRASS], lightEnable);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(0.0f, 0.f, -125.0f);
		modelStack.Rotate(-90, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(20.f, 150.f, 1.f);
		this->RenderMesh(MeshHandler::getMesh(GEO_RUNNINGFLOOR), lightEnable);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(0.0f, 0.4f, 0.0f);
	//modelStack.Rotate(90, 0.0f, 1.0f, 0.0f);
	modelStack.Rotate(2, 1.0f, 0.0f, 0.0f);
	modelStack.Scale(0.1f, 0.1f, 0.1f);
	this->RenderMesh(meshList[GEO_OBJ_FENCE], lightEnable);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//modelStack.Translate(9.0f, 0.7f, 0.0f);
	modelStack.Rotate(00, 0.0f, 1.0f, 0.0f);
	modelStack.Scale(0.05f, 0.05f, 0.05f);
	this->RenderMesh(MeshHandler::getMesh(GEO_SONIC_TAILS), lightEnable);
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
		this->RenderText(meshList[GEO_TEXT], "Speed Upgrade Shop", Color(0.9, 0.7, 0.01));
		
		modelStack.PushMatrix();
			modelStack.Translate(0.2, -1, 0.2);
			modelStack.Rotate(0, 0.0f, 1.0f, 0.0f);
			modelStack.Scale(1.0f, 1.0f, 1.0f);
			ss << "Level ("<< playerSpeedLevel <<"/"<<maxPlayerSpeedLevel<<"): " << std::setprecision(2) << playerSpeed/defaultSpeed << "x Speed";
			this->RenderText(meshList[GEO_TEXT], ss.str(), Color(0.9, 0.7, 0.01));


		modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-3.0, 8, -50.0);
		modelStack.Rotate(0, 0.0f, 1.0f, 0.0f);
		modelStack.Scale(3.0f, 3.0f, 3.0f);
		ss.str("");
		ss.clear();
		ss << "RUNNER";
		this->RenderText(meshList[GEO_TEXT], ss.str(), Color(1.0 - rainbow * 0.5, pow(rainbow,0.5), rainbow));

		modelStack.PushMatrix();
			modelStack.Translate(-1.0, -0.42, 0.0);
			modelStack.Rotate(0, 0.0f, 1.0f, 0.0f);
			modelStack.Scale(0.5f, 0.5f, 0.5f);
			ss.str("");
			ss.clear();
			ss << "Interact to Start";
			this->RenderText(meshList[GEO_TEXT], ss.str(), Color(0.9, 0.8, 0.0));

		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(-0.1, -1.04, 0.0);
			modelStack.Rotate(0, 0.0f, 1.0f, 0.0f);
			modelStack.Scale(0.33f, 0.33f, 0.33f);
			ss.str("");
			ss.clear();
			float PB = 99999;
			int loc = -1;
			for (int i = 0; i < racingScores.size(); i++) {
				if (racingScores.at(i) < PB) {
					PB = racingScores.at(i);
					loc = i;
				}
			}
			ss << "PBest Time: " << getRacingTime(loc);
			this->RenderText(meshList[GEO_TEXT], ss.str(), Color(0.4, 1.0, 1.0));
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
			RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0.8, 0.6, 1.0), 3.5, 7, textYStart-offset*i);
			i++;
		}
		//Renders Press E to close
		ss.str("");
		ss.clear();
		ss << "Press E to " << (currentMessage+1 == queuedMessages.size() ? "Close" : "Continue");
		RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0.8, 0.6, 1.0), 3.5, 40, textYStart - offset * (++i < 4? 4: i));
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
			RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0.1, 0.4, 0.1), 4, 10, 20-offset*i);
			i++;
		}

	}

	//Coins UI
	RenderMeshOnScreen(meshList[GEO_COINS_METER], 9, 55, 15, 13);
	
	ss.str("");
	ss.clear();
	std::string bal = std::to_string(coinBalance);
	if (coinBalance < 10) bal = "0" + bal;
	if (coinBalance < 100) bal = "0" + bal;
	if (coinBalance > 999) bal = "999";
	ss << bal;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 0, 0), 5, 7, 52.5);

	//Time UI
	RenderMeshOnScreen(meshList[GEO_TIME_METER], 9, 49, 15, 13);
	RenderTextOnScreen(meshList[GEO_TEXT], getRacingTime(racingScores.size()-1), Color(0, 0, 0), 4, 7, 46.5);
	RenderTextOnScreen(meshList[GEO_TEXT], getRacingTimeMilliCounter(racingScores.size() - 1), Color(0, 0, 0), 2, 12, 49.5);

	////Interaction MSG UI
	if (canInteractWithSomething && !isInteracting) {
		ss.str("");
		ss.clear();
		ss << "Press 'E' to Interact";
		RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 1, 1), 4, 20, 10);
	}
	
	//FPS UI
	ss.str("");
	ss.clear();
	ss << "FPS: " << this->elapsed;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 4, 0, 5);

	//XYZ UI
	ss.str("");
	ss.clear();
	ss << "X: " << player->getEntityData()->transX;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 4, 0, 15);

	ss.str("");
	ss.clear();
	ss << "Y: " << player->getEntityData()->transY;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 4, 0, 12);

	ss.str("");
	ss.clear();
	ss << "Z: " << player->getEntityData()->transZ;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 4, 0, 8);
}

void SceneAssignment2::RenderSkybox() {
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
		modelStack.PushMatrix();
		modelStack.Translate(-250.0f, 0.0f, 0.0f);
		modelStack.Rotate(90, 0.0f, 1.0f, 0.0f);
		modelStack.Scale(500.0f, 500.0f, 500.0f);
		this->RenderMesh(meshList[GEO_SKY_LEFT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(250.0f, 0.0f, 0.0f);
		modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f);
		modelStack.Scale(500.0f, 500.0f, 500.0f);
		this->RenderMesh(meshList[GEO_SKY_RIGHT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0.0f, 250.0f, 0.0f);
		modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f);
		modelStack.Rotate(90, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(500.0f, 500.0f, 500.0f);
		this->RenderMesh(meshList[GEO_SKY_TOP], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0.0f, -250.0f, 0.0f);
		modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f);
		modelStack.Rotate(90, -1.0f, 0.0f, 0.0f);
		modelStack.Scale(500.0f, 500.0f, 500.0f);
		this->RenderMesh(meshList[GEO_SKY_BOTTOM], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0.0f, 0.0f, -250.0f);
		modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(500.0f, 500.0f, 500.0f);
		this->RenderMesh(meshList[GEO_SKY_BACK], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0.0f, 0.0f, 250.0f);
		modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
		modelStack.Scale(500.0f, 500.0f, 500.0f);
		this->RenderMesh(meshList[GEO_SKY_FRONT], false);
		modelStack.PopMatrix();

	modelStack.PopMatrix();
}

bool SceneAssignment2::passedInteractCooldown() {
	const float INTERACTION_COOLDOWN = 0.5f;
	if (latestInteractionSwitch + INTERACTION_COOLDOWN < this->elapsed) {
		return true;
	}
	return false;
}

int SceneAssignment2::getCoins() {
	return coinBalance;
}

void SceneAssignment2::setCoins(int val) {
	coinBalance = val;
}

void SceneAssignment2::addCoins(int val) {
	coinBalance += val;
}

void SceneAssignment2::sendNotification(std::string msg, double duration) {
	showNotifUntil = elapsed + duration;
	notificationMessage = msg;
}

std::string SceneAssignment2::getRacingTime(int index) {
	if (!(index >= 0 && index < racingScores.size())) {
		return "0:00";
	}
	float racingScore = racingScores.at(index);
	int min = racingScore / 60;
	int sec = racingScore - min * 60;
	std::string str = std::to_string(min) + ":" + (sec < 10 ? "0" : "") + std::to_string(sec);
	return str;
}

std::string SceneAssignment2::getRacingTimeMilliCounter(int index) {
	if (!(index >= 0 && index < racingScores.size())) {
		return "000";
	}
	float racingScore = racingScores.at(index);
	int millis = (racingScore - (int)racingScore) * 1000.0;
	if (millis > 999) millis = 999;
	std::string str = std::to_string(millis);
	if (millis < 10) str = "0" + str;
	if (millis < 100) str = "0" + str;
	return str;
}

void SceneAssignment2::split(std::string txt, char delim, std::vector<std::string>& out) {
	std::istringstream iss(txt);
	std::string item;
	while (std::getline(iss, item, delim)) {
		out.push_back(item);
	}
}

bool SceneAssignment2::runCommand(std::string cmd) {
	std::vector<std::string> splitVar;
	split(cmd, ' ', splitVar);

	if (splitVar.size() == 1) {
		if (splitVar.at(0) == "/startrace") {
			Application::changeToScene("RunningScene", std::to_string(playerSpeed));
			return true;
		}
		else if (splitVar.at(0) == "/endinteraction") {
			EndInteraction();
			return true;
		}
		else if (splitVar.at(0) == "/unlockrace") {
			raceUnlocked = true;
			sendNotification("Race has been UNLOCKED", 5.0);
			return true;
		}
		else if (splitVar.at(0) == "/buyupgrade") {
			buySpeedUpgrade();
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

bool SceneAssignment2::buySpeedUpgrade() {
	if (playerSpeedLevel < maxPlayerSpeedLevel) {
		if (coinBalance > upgradeCost[this->playerSpeedLevel]) {
			coinBalance -= upgradeCost[this->playerSpeedLevel];
			playerSpeedLevel++;
			playerSpeed = defaultSpeed * (1 + 0.1 * playerSpeedLevel);
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

void SceneAssignment2::addNewTimingScore(float score) {
	this->racingScores.push_back(score);
}

bool SceneAssignment2::loadInteractions(INTERACTION_TYPE type) {
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
			inter->interactionText = "0 minutes and 27 seconds!";
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

			Interaction* inter;
			inter = new Interaction();
			inter->interactionText = "Good Luck!\nRacing begins as you close this\n";
			inter->postInteractionCMD.push_back("/startrace");
			queuedMessages.push_back(inter);

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

void SceneAssignment2::nextInteraction() {
	if (currentMessage > 0) { //Post Interaction CMDs to execute (Interaction prior to the one being moved to now)
		for (auto& entry : queuedMessages.at(currentMessage)->postInteractionCMD) {
			this->runCommand(entry);
		}
	}
	currentMessage += 1;
	if (queuedMessages.size() < currentMessage + 1) {
		for (auto& entry : queuedMessages.at(currentMessage-1)->postInteractionCMD) {
			this->runCommand(entry);
		}
		EndInteraction();
	}
	else {
		for (auto& entry : queuedMessages.at(currentMessage)->preInteractionCMD) { //Pre Interaction CMDs to execute
			this->runCommand(entry);
		}
	}
}

void SceneAssignment2::EndInteraction() {
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

void SceneAssignment2::Exit()
{
	// Cleanup VBO here
	this->EndInteraction(); //To clear up queuedMessages pointers

	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}