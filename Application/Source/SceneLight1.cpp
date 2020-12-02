#include "SceneLight1.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include <Windows.h>

#include "shader.hpp"
#include "Utility.h"


SceneLight1::SceneLight1()
{
	rotateAngle = 0;
	rotateAngle2 = 0;
	translateZ = 1;
	scaleAll = 1;

	rotateAngleFWD = true;
	translateZFWD = true;
	scaleALLFWD = true;
}

SceneLight1::~SceneLight1()
{
}

void SceneLight1::Init() {

	// Init VBO here
	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//Shading.fragmentshader");
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
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
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
	light[0].position.set(0, 20, 0); 
	light[0].color.set(1, 1, 1); //set to white light
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	// Make sure you pass uniform parameters after glUseProgram()
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);


	//Universal material template used for testing
	Material mat;
	mat.kAmbient.Set(0.3f, 0.3f, 0.3f);
	mat.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	mat.kSpecular.Set(0.3f, 0.3f, 0.3f);
	mat.kShininess = 1.0f;
	meshList[GEO_CUBE] = MeshBuilder::GenerateHalfCone("cube", Color(0.9f, 0.6f, 0.3f), 3, 10);
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes", 1, 1, 1);
	//meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", 1, 1);
	//meshList[GEO_SUN] = MeshBuilder::GenerateSphere("sun", Color(0.956f, 0.5f, 0.215f), 3);
	meshList[GEO_SONICHEAD] = MeshBuilder::GenerateSphere("sonichead", Color(0.188f, 0.3804f, 0.89019f));
	meshList[GEO_SONICEYEBALL] = MeshBuilder::GenerateSphere("soniceyeball", Color(0.95f, 0.95f, 0.95f));
	meshList[GEO_SONICGREENEYE] = MeshBuilder::GenerateSphere("sonicgreeneyeball", Color(0.482f, 0.7686f, 0.235f));
	meshList[GEO_SONICBLACKEYE] = MeshBuilder::GenerateSphere("sonicblackeyeball", Color(0.05f, 0.05f, 0.05f));
	meshList[GEO_SONICEARS] = MeshBuilder::GenerateTetahedron("sonicears", Color(0.188f, 0.3804f, 0.89019f));
	meshList[GEO_INNERSONICEARS] = MeshBuilder::GenerateTetahedron("sonicinnerears", Color(0.9647f, 0.7843f, 0.5176f));

	meshList[GEO_MOUTHTORUS] = MeshBuilder::GenerateTorus("sonictorus", Color(0.98039f, 0.8392f, 0.62745f), 0.2, 0.4);
	meshList[GEO_MOUTHSPHERE] = MeshBuilder::GenerateHemiSphere("sonicsphere", Color(0.98039f, 0.8392f, 0.62745f));

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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void SceneLight1::Update(double dt)
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
}


void SceneLight1::Render()
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

	
	//Main model: head
	modelStack.PushMatrix();
		modelStack.Translate(0.0f, 0.0f, 0.0f);
		modelStack.Rotate(-10, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(2.0f, 2.0f, 2.0f);
		this->RenderMesh(meshList[GEO_SONICHEAD], true);

		//Eyes
		modelStack.PushMatrix();
			modelStack.Rotate(10, 0.0f, 0.0f, 1.0f);
			modelStack.Translate(-0.3f, -0.15f, 0.94f);
			modelStack.Rotate(-10, 0.0f, 1.0f, 0.0f);
			modelStack.Scale(0.135f, 0.3f, 0.135f);
			this->RenderMesh(meshList[GEO_SONICEYEBALL], true);

			modelStack.PushMatrix();
				modelStack.Rotate(-5, 0.0f, 0.0f, 1.0f);
				modelStack.Translate(0.35f, -0.4f, 0.7f);
				modelStack.Rotate(17, 1.0f, 0.0f, 0.0f);
				modelStack.Scale(0.3f, 0.3f, 0.3f);
				this->RenderMesh(meshList[GEO_SONICGREENEYE], true);

				modelStack.PushMatrix();
					modelStack.Translate(0.10f, 0.0f, 0.7f);
					modelStack.Rotate(0, 1.0f, 1.0f, 1.0f);
					modelStack.Scale(0.7f, 0.58f, 0.7f);
					this->RenderMesh(meshList[GEO_SONICBLACKEYE], true);
				
					modelStack.PopMatrix();
			modelStack.PopMatrix();
		modelStack.PopMatrix();
		
		//Eyes 2
		modelStack.PushMatrix();
			modelStack.Rotate(-10, 0.0f, 0.0f, 1.0f);
			modelStack.Translate(0.3f, -0.15f, 0.94f);
			modelStack.Rotate(10, 0.0f, 1.0f, 0.0f);
			modelStack.Scale(0.135f, 0.3f, 0.135f);
			this->RenderMesh(meshList[GEO_SONICEYEBALL], true);

			modelStack.PushMatrix();
				modelStack.Rotate(-5, 0.0f, 1.0f, 0.0f);
				modelStack.Translate(-0.35f, -0.4f, 0.7f);
				modelStack.Rotate(-17, 0.0f, 1.0f, 0.0f);
				modelStack.Rotate(17, 1.0f, 0.0f, 0.0f);
				modelStack.Scale(0.3f, 0.3f, 0.3f);
				this->RenderMesh(meshList[GEO_SONICGREENEYE], true);

				modelStack.PushMatrix();
					modelStack.Translate(0.10f, 0.0f, 0.7f);
					modelStack.Rotate(0, 1.0f, 1.0f, 1.0f);
					modelStack.Scale(0.7f, 0.58f, 0.7f);
					this->RenderMesh(meshList[GEO_SONICBLACKEYE], true);

				modelStack.PopMatrix();
			modelStack.PopMatrix();
		modelStack.PopMatrix();

		//Ears 1
		modelStack.PushMatrix();
			modelStack.Translate(0.55f, 0.8f, 0.3f);
			modelStack.Rotate(10, 1.0f, 0.0f, 0.0f);
			modelStack.Rotate(-27, 0.0f, 0.0f, 1.0f);
			modelStack.Rotate(-5, 0.0f, 1.0f, 0.0f);
			modelStack.Scale(0.55f, 0.55f, 0.75f);
			this->RenderMesh(meshList[GEO_SONICEARS], true);

			modelStack.PushMatrix();
				modelStack.Translate(0.0f, 0.0f, 0.06f);
				modelStack.Scale(0.8f, 0.8f, 0.8f);
				this->RenderMesh(meshList[GEO_INNERSONICEARS], true);

			modelStack.PopMatrix();

		modelStack.PopMatrix();


		//Ears 2
		modelStack.PushMatrix();
			modelStack.Translate(-0.55f, 0.8f, 0.3f);
			modelStack.Rotate(10, 1.0f, 0.0f, 0.0f);
			modelStack.Rotate(27, 0.0f, 0.0f, 1.0f);
			modelStack.Rotate(5, 0.0f, 1.0f, 0.0f);
			modelStack.Scale(0.55f, 0.55f, 0.75f);
			this->RenderMesh(meshList[GEO_SONICEARS], true);

			modelStack.PushMatrix();
				modelStack.Translate(0.0f, 0.0f, 0.06f);
				modelStack.Scale(0.8f, 0.8f, 0.8f);
				this->RenderMesh(meshList[GEO_INNERSONICEARS], true);

			modelStack.PopMatrix();

		modelStack.PopMatrix();

		//Mouth
		modelStack.PushMatrix();
			modelStack.Rotate(10, 1.0f, 0.0f, 0.0f);
			modelStack.Translate(0.0f, -0.4f, 0.1f);
			modelStack.Rotate(20, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(1.4f, 0.55f, 1.4f);
			this->RenderMesh(meshList[GEO_MOUTHTORUS], true);

			modelStack.PushMatrix();
				modelStack.Translate(0.0f, 0.0f, 0.53f);
				//modelStack.Rotate(30, 1.0f, 0.0f, 0.0f);
				modelStack.Scale(0.2f, 0.3f, 0.08f);
				this->RenderMesh(meshList[GEO_MOUTHSPHERE], true);
			modelStack.PopMatrix();

		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(0.f, 0.4f, -0.8f);
			modelStack.Rotate(30, 1.0f, 0.0f, 0.0f);
			modelStack.Scale(0.45f, 0.65f, 1.4f);
			this->RenderMesh(meshList[GEO_HAIRHEMISPHERE], true);

			modelStack.PushMatrix();
				modelStack.Translate(0.f, 0.0f, 0.0f);
				modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);
				modelStack.Scale(1.0f, 0.5f, 1.0f);
				this->RenderMesh(meshList[GEO_HAIRHEMISPHERE], true);

				modelStack.PushMatrix();
					
					modelStack.Translate(0.f, 0.0f, -2.90f);
					modelStack.Rotate(30, 1.0f, 0.0f, 0.0f);
					modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);
					modelStack.Scale(0.6f, 2.0f, 0.3f);
					this->RenderMesh(meshList[GEO_HAIRHEMISPHERE], true);


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

void SceneLight1::RenderMesh(Mesh* mesh, bool enableLight)
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

void SceneLight1::Exit()
{
	// Cleanup VBO here

	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
