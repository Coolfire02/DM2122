#include "SceneAssignment2.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "LoadTGA.h"
#include <Windows.h>
#include <sstream>

#include "shader.hpp"
#include "Utility.h"


SceneAssignment2::SceneAssignment2() : eManager(this), defaultSpeed(15.f)
{
	playerSpeed = defaultSpeed;
	rotateAngle = 0;
	rotateAngle2 = 0;
	translateZ = 1;
	scaleAll = 1;
	fps = 0;
	lightEnable = false;
	hitboxEnable = false;

	rotateAngleFWD = true;
	translateZFWD = true;
	scaleALLFWD = true;
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
	eManager.spawnMovingEntity(player);



	Mesh* coinMesh = MeshHandler::getMesh(GEOMETRY_TYPE::GEO_COIN);
	Entity* newCoin = new Coin(this, new Box(coinMesh->botLeftPos, coinMesh->topRightPos), "Coin");
	newCoin->getEntityData()->rotXMag = 90.f;
	newCoin->getEntityData()->transX = 8.0;
	eManager.spawnWorldEntity(newCoin);

	Entity* eggman = new NPC(this, NPCTYPE::EGGMAN, "Eggman");
	eggman->getEntityData()->scaleX = 0.04;
	eggman->getEntityData()->scaleY = 0.04;
	eggman->getEntityData()->scaleZ = 0.04;
	eggman->getEntityData()->transX = 11;
	eggman->getEntityData()->transY = 0;
	eggman->getEntityData()->transZ = -22;
	eggman->getEntityData()->rotYMag = -27.f;
	eManager.spawnWorldEntity(eggman);

	Entity* eggmanInteractZone = new CustomEntity(this, new Box(new Position3D(-5, 0, 4), new Position3D(5, 1, -4)), "interaction_eggman");
	eggmanInteractZone->getEntityData()->transX = eggman->getEntityData()->transX;
	eggmanInteractZone->getEntityData()->transY = eggman->getEntityData()->transY;
	eggmanInteractZone->getEntityData()->transZ = eggman->getEntityData()->transZ;
	eManager.spawnWorldEntity(eggmanInteractZone);

	Entity* podium = new WorldObject(this, GEO_PODIUM_1ST, "Podium_1st");
	podium->getEntityData()->transX = 32.0f;
	podium->getEntityData()->scaleX = 6;
	podium->getEntityData()->scaleY = 3;
	podium->getEntityData()->scaleZ = 6;
	eManager.spawnWorldEntity(podium);

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

	//Camera init(starting pos, where it looks at, up
	camera.Init(Vector3(player->getEntityData()->transX, player->getEntityData()->transY-2, player->getEntityData()->transZ), Vector3(0, 0, 1), Vector3(0, 1, 0));

	//Light init
	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.set(0, 20, 0);
	light[0].color.set(1, 1, 1); //set to white light
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	//2nd line
	light[1].type = Light::LIGHT_DIRECTIONAL;
	light[1].position.set(0, 1000, 0);
	light[1].color.set(0.8, 0, 0.7); //set to white light
	light[1].power = 1;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);

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

	//Week 7 - Code to change number of lights
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

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

	meshList[GEO_OBJ_WINNERPODIUM] = MeshBuilder::GenerateOBJ("podium", "OBJ//winner_podium.obj");
	meshList[GEO_OBJ_WINNERPODIUM]->textureID = LoadTGA("Image//winner_podium.tga");
	meshList[GEO_OBJ_WINNERPODIUM]->material = mat;

	///*meshList[GEO_OBJ_ISLAND] = MeshBuilder::GenerateOBJ("island", "OBJ//island.obj");
	//meshList[GEO_OBJ_ISLAND]->textureID = LoadTGA("Image//island.tga");*/

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_PLATFORM_FLOOR] = MeshBuilder::GenerateQuad("floor", Color(1, 1, 1));
	meshList[GEO_PLATFORM_FLOOR]->textureID = LoadTGA("Image//SonicFloor.tga");



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

	std::vector<CollidedWith*> collided = eManager.preCollisionUpdate(); 
	for (auto& entry : collided) {
		if (entry->attacker->getType() == ENTITYTYPE::SONIC) {

			if (entry->victim->getType() == ENTITYTYPE::LIVE_NPC || entry->victim->getType() == ENTITYTYPE::WORLDOBJ) {
				entry->cancelled = true;
			}

			std::cout << "Collided" << std::endl;

			//entry->victim->setDead(true);
			//std::cout << "Cancelled collision" << std::endl;
		}
	}
	eManager.collisionUpdate(dt);

	if (player->usingNewData()) { //Aka movement not cancelled
		camera.Move(player->getEntityData()->transX - player->getOldEntityData()->transX,
			player->getEntityData()->transY - player->getOldEntityData()->transY,
			player->getEntityData()->transZ - player->getOldEntityData()->transZ);
	}
	

	eManager.postCollisionUpdate();

	//player->getEntityData()->scaleX += 0.1 * dt;
	//player->getEntityData()->rotYMag += 1 * dt;

	rotateAngle += 10 * dt;
	rotateAngle2 += 50 * dt;

	fps = 1 / dt;

	if (translateZFWD) {
		translateZ += 0.2;
		if (translateZ >= 5) {
			translateZFWD = false;
		}
	}
	else {
		translateZ -= 0.2;
		if (translateZ <= 1) {
			translateZFWD = true;
		}
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

	if (Application::IsKeyPressed('5')) {
		//to do: switch light type to POINT and pass the information to shader
		light[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('6')) {
		//to do: switch light type to DIRECTIONAL and pass the information to shader
		light[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('7')) {
		//to do: switch light type to SPOT and pass the information to shader
		light[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	if (Application::IsKeyPressed('9')) {
		hitboxEnable = !hitboxEnable;
	}
	if (Application::IsKeyPressed('0')) {
		lightEnable = !lightEnable;
	}

	const float LSPEED = 10.f;
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
	}
		//player->getEntityData()->transX -= (float)(LSPEED * dt);
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
	}
		//player->getEntityData()->transX += (float)(LSPEED * dt);

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
	modelStack.Translate(0.0f, 0.4f, 0.0f);
	//modelStack.Rotate(90, 0.0f, 1.0f, 0.0f);
	modelStack.Rotate(2, 1.0f, 0.0f, 0.0f);
	modelStack.Scale(0.1f, 0.1f, 0.1f);
	this->RenderMesh(meshList[GEO_OBJ_FENCE], lightEnable);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(9.0f, 0.7f, 0.0f);
	modelStack.Rotate(00, 0.0f, 1.0f, 0.0f);
	modelStack.Scale(0.05f, 0.05f, 0.05f);
	this->RenderMesh(meshList[GEO_SONIC_TAILS], lightEnable);
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

	RenderMeshOnScreen(meshList[GEO_COINS_METER], 9, 55, 15, 13);
	std::ostringstream ss;
	ss << "000";
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 0, 0), 5, 7, 52.5);

	RenderMeshOnScreen(meshList[GEO_TIME_METER], 9, 49, 15, 13);
	RenderTextOnScreen(meshList[GEO_TEXT], "0:00", Color(0, 0, 0), 4, 7, 46.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "999", Color(0, 0, 0), 2, 12, 49.5);

	ss.str("");
	ss.clear();
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 4, 0, 5);

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



void SceneAssignment2::Exit()
{
	// Cleanup VBO here

	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}