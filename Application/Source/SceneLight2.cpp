#include "SceneLight2.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include <Windows.h>

#include "shader.hpp"
#include "Utility.h"


SceneLight2::SceneLight2()
{
	rotateAngle = 0;
	rotateAngle2 = 0;
	translateZ = 1;
	scaleAll = 1;

	rotateAngleFWD = true;
	translateZFWD = true;
	scaleALLFWD = true;
}

SceneLight2::~SceneLight2()
{
}

void SceneLight2::Init() {

	// Init VBO here
	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//LightSource.fragmentshader");
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

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	glUseProgram(m_programID);

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 8.0f / 6.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);

	//Camera init(starting pos, where it looks at, up
	camera.Init(Vector3(10, 7, 3), Vector3(0,0,0), Vector3(0,1,0));

	//Light init
	light[0].type = Light::LIGHT_POINT;
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
	light[1].type = Light::LIGHT_SPOT;
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
	glUniform1i(m_parameters[U_NUMLIGHTS], 2);

	//Universal material template used for testing
	Material mat;
	mat.kAmbient.Set(0.1f, 0.1f, 0.1f);
	mat.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	mat.kSpecular.Set(0.3f, 0.3f, 0.3f);
	mat.kShininess = 1.0f;
	meshList[GEO_CUBE] = MeshBuilder::GenerateCylinder("cube", Color(0.9f, 0.6f, 0.3f), 5);
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes", 1, 1, 1);
	//meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", 1, 1);
	//meshList[GEO_SUN] = MeshBuilder::GenerateSphere("sun", Color(0.956f, 0.5f, 0.215f), 3);
	meshList[GEO_SONICHEAD] = MeshBuilder::GenerateHalfTorus("sonichead", Color(0.188f, 0.3804f, 0.89019f), 1.2, 2.2);
	meshList[GEO_SONICEYEBALL] = MeshBuilder::GenerateSphere("soniceyeball", Color(0.95f, 0.95f, 0.95f));
	meshList[GEO_SONICGREENEYE] = MeshBuilder::GenerateSphere("sonicgreeneyeball", Color(0.482f, 0.7686f, 0.235f));
	meshList[GEO_SONICBLACKEYE] = MeshBuilder::GenerateSphere("sonicblackeyeball", Color(0.05f, 0.05f, 0.05f));
	meshList[GEO_SONICEARS] = MeshBuilder::GenerateTetahedron("sonicears", Color(0.188f, 0.3804f, 0.89019f));
	meshList[GEO_INNERSONICEARS] = MeshBuilder::GenerateTetahedron("sonicinnerears", Color(0.9647f, 0.7843f, 0.5176f));

	meshList[GEO_MOUTHTORUS] = MeshBuilder::GenerateTorus("sonictorus", Color(0.98039f, 0.8392f, 0.62745f), 0.2, 0.4);
	meshList[GEO_MOUTHSPHERE] = MeshBuilder::GenerateHemiSphere("sonicsphere", Color(0.98039f, 0.8392f, 0.62745f));
	meshList[GEO_HAIRHEMISPHEREFRUSTUM] = MeshBuilder::GenerateHemiSphereFrustum("sonichairhemifrustum", Color(0.188f, 0.3804f, 0.89019f), 120);
	meshList[GEO_HAIRHEMISPHERE] = MeshBuilder::GenerateHemiSphere("sonichairhemi", Color(0.188f, 0.3804f, 0.89019f));
	meshList[GEO_HAIRCONE] = MeshBuilder::GenerateCone("sonichaircone", Color(0.188f, 0.3804f, 0.89019f), 1, 2);
	meshList[GEO_HAIRHALFCONE] = MeshBuilder::GenerateHalfCone("sonichairhalfcone", Color(0.188f, 0.3804f, 0.89019f), 1, 2);

	//meshList[GEO_PLANET2] = MeshBuilder::GenerateSphere("planet2", Color(0.8f, 0.82f, 0.8f), 1);
	//meshList[GEO_PLANET3] = MeshBuilder::GenerateSphere("planet3", Color(0.4f, 0.9f, 0.77f), 1);
	//meshList[GEO_PLANET4] = MeshBuilder::GenerateSphere("planet4", Color(0.88f, 0.4f, 0.123f), 1);
	//meshList[GEO_PLANET5] = MeshBuilder::GenerateSphere("planet5", Color(0.88f, 0.88f, 0.65f), 1);
	//meshList[GEO_PLANET6] = MeshBuilder::GenerateSphere("planet6", Color(0.8f, 1.0f, 0.85f), 1);
	//meshList[GEO_PLANET7] = MeshBuilder::GenerateSphere("planet7", Color(0.2f, 0.0f, 0.2f), 1);
	//meshList[GEO_PLANET8] = MeshBuilder::GenerateSphere("planet8", Color(0.05f, 0.05f, 0.05f), 1);
	
	meshList[GEO_LEGCYLINDER] = MeshBuilder::GenerateCylinder("soniclegcylinder", Color(0.188f, 0.3804f, 0.89019f), 1);
	meshList[GEO_LEGTORUS] = MeshBuilder::GenerateTorus("soniclegtorus", Color(1.0f, 1.0f, 1.0f), 1.2, 2.5);
	meshList[GEO_LEGHEMISPHERE] = MeshBuilder::GenerateHemiSphere("sonicleghemisphere", Color(0.188f, 0.3804f, 0.89019f));
	meshList[GEO_LEGSPHERE] = MeshBuilder::GenerateSphere("soniclegsphere", Color(0.188f, 0.3804f, 0.89019f));

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightbulll", Color(1.0f, 1.0f, 1.0f));

	meshList[GEO_CUBE]->material = mat;
	meshList[GEO_SONICHEAD]->material = mat;
	meshList[GEO_SONICEYEBALL]->material = mat;
	meshList[GEO_SONICGREENEYE]->material = mat;
	meshList[GEO_SONICBLACKEYE]->material = mat;

	meshList[GEO_MOUTHTORUS]->material = mat;
	meshList[GEO_MOUTHSPHERE]->material = mat;

	meshList[GEO_SONICEARS]->material = mat;
	meshList[GEO_INNERSONICEARS]->material = mat;

	meshList[GEO_HAIRHEMISPHERE]->material = mat;
	meshList[GEO_HAIRCONE]->material = mat;
	meshList[GEO_HAIRHALFCONE]->material = mat;
	meshList[GEO_HAIRHEMISPHEREFRUSTUM]->material = mat;

	meshList[GEO_LEGCYLINDER]->material = mat;
	//meshList[GEO_LEGTORUS]->material = mat;
	meshList[GEO_LEGHEMISPHERE]->material = mat;


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void SceneLight2::Update(double dt)
{
	camera.Update(dt);
		rotateAngle += 10*dt;
		rotateAngle2 += 50 * dt;

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

	const float LSPEED = 10.f;
	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);
	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

	lightPosition_cameraspace = viewStack.Top() * light[1].position;
	glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
}


void SceneLight2::Render()
{

	glEnableVertexAttribArray(0); // 1st attribute buffer: vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer: color

	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 model;
	Mtx44 view;

	Mtx44 MVP;

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
	
	modelStack.PushMatrix();
		modelStack.Translate(0.0f, -4.0f, 0.0f);
		modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(100.0f, 1.0f, 100.0f);
		this->RenderMesh(meshList[GEO_CUBE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.0f, 0.0f, 5.0f);
	modelStack.Rotate(-10, 1.0f, 0.0f, 0.0f);
	modelStack.Scale(2.0f, 2.0f, 2.0f);
	this->RenderMesh(meshList[GEO_SONICHEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.0f, 0.0f, -5.0f);
	modelStack.Rotate(-10, 1.0f, 0.0f, 0.0f);
	modelStack.Scale(2.0f, 2.0f, 2.0f);
	this->RenderMesh(meshList[GEO_SONICHEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(5.0f, 0.0f, 5.0f);
	modelStack.Rotate(-10, 1.0f, 0.0f, 0.0f);
	modelStack.Scale(2.0f, 2.0f, 2.0f);
	this->RenderMesh(meshList[GEO_SONICHEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-5.0f, 0.0f, 5.0f);
	modelStack.Rotate(-10, 1.0f, 0.0f, 0.0f);
	modelStack.Scale(2.0f, 2.0f, 2.0f);
	this->RenderMesh(meshList[GEO_SONICHEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(5.0f, 0.0f, -5.0f);
	modelStack.Rotate(-10, 1.0f, 0.0f, 0.0f);
	modelStack.Scale(2.0f, 2.0f, 2.0f);
	this->RenderMesh(meshList[GEO_SONICHEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-5.0f, 0.0f, -5.0f);
	modelStack.Rotate(-10, 1.0f, 0.0f, 0.0f);
	modelStack.Scale(2.0f, 2.0f, 2.0f);
	this->RenderMesh(meshList[GEO_SONICHEAD], true);
	modelStack.PopMatrix();



	//Main model: head
	modelStack.PushMatrix();

	modelStack.Translate(0.2f, -0.4f, 0.0f);
	modelStack.Rotate(5, 0.0f, 0.0f, 1.0f);

	modelStack.Rotate(0, 1.0f, 0.0f, 0.0f); //to go back

	modelStack.Scale(0.12f, 0.12f, 0.12f);
	this->RenderMesh(meshList[GEO_LEGHEMISPHERE], true);

	modelStack.PushMatrix();

	modelStack.Translate(0.f, -2.8f, 0.0f);
	modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
	modelStack.Scale(1.0, 5.6f, 1.0f);
	this->RenderMesh(meshList[GEO_LEGCYLINDER], true);

	modelStack.PushMatrix();

	modelStack.Scale(1.0, 0.1785f, 1.0f);

	modelStack.Translate(0.f, -2.9f, 0.0f);
	modelStack.Rotate(90, 1.0f, 0.0f, 0.0f);

	this->RenderMesh(meshList[GEO_LEGSPHERE], true);

	modelStack.PushMatrix();

	modelStack.Translate(0.f, -3.2f, 0.1f);
	modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
	modelStack.Scale(0.85, 5.6f, 0.85f);
	this->RenderMesh(meshList[GEO_LEGCYLINDER], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PopMatrix();


	//scale.SetToScale(1, 1, 1);
	//rotate.SetToRotation(0, 0.0f, 0.0f, 1.0f);
	//translate.SetToTranslation(0, 0, 0.0);
	//model = translate * rotate * scale;
	//MVP = projection * view * model;
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	//meshList[GEO_SPHERE]->Render();
	//
	//
	//
	//translate.SetToIdentity();
	//rotate.SetToIdentity();
	//scale.SetToIdentity();

	//scale.SetToScale(1, 1, 1);
	//rotate.SetToRotation(rotateAngle, 0.0f, 0.0f, 1.0f);
	//translate.SetToTranslation(0, 0, translateZ);
	//model = translate * rotate * scale;
	//MVP = projection * view * model;
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);


	//meshList[GEO_CONE]->Render();

	//translate.SetToIdentity();
	//rotate.SetToIdentity();
	//scale.SetToIdentity();

	//scale.SetToScale(1, 1, -1);
	//rotate.SetToRotation(rotateAngle, 0.0f, 0.0f, 1.0f);
	//translate.SetToTranslation(0, 0, -translateZ);
	//model = translate * rotate * scale;
	//MVP = projection * view * model;
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);


	//meshList[GEO_CYLINDER]->Render();
	

	

	
}

void SceneLight2::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	mesh->Render();
}

void SceneLight2::Exit()
{
	// Cleanup VBO here

	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
