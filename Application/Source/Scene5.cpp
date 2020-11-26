#include "Scene5.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include <Windows.h>

#include "shader.hpp"


Scene5::Scene5()
{
	rotateAngle = 0;
	rotateAngle2 = 0;
	translateZ = 1;
	scaleAll = 1;

	rotateAngleFWD = true;
	translateZFWD = true;
	scaleALLFWD = true;
}

Scene5::~Scene5()
{
}

void Scene5::Init() {

	// Init VBO here
	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	glUseProgram(m_programID);

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// An array of 3 buffers

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 8.0f / 6.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);

	//Camera init(starting pos, where it looks at, up
	Color color(1.0f, 1.0f, 1.0f);

	camera.Init(Vector3(20, 15, 3), Vector3(0,0,0), Vector3(0,1,0));

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", 1, 1, 1);
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes", 1, 1, 1);
	meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", 1, 1);
	meshList[GEO_SUN] = MeshBuilder::GenerateSphere("sun", Color(0.956f, 0.5f, 0.215f), 3);
	meshList[GEO_PLANET1] = MeshBuilder::GenerateSphere("planet1", Color(0.7725f, 0.396f, 0.396f), 1);
	meshList[GEO_PLANET2] = MeshBuilder::GenerateSphere("planet2", Color(0.8f, 0.82f, 0.8f), 1);
	meshList[GEO_PLANET3] = MeshBuilder::GenerateSphere("planet3", Color(0.4f, 0.9f, 0.77f), 1);
	meshList[GEO_PLANET4] = MeshBuilder::GenerateSphere("planet4", Color(0.88f, 0.4f, 0.123f), 1);
	meshList[GEO_PLANET5] = MeshBuilder::GenerateSphere("planet5", Color(0.88f, 0.88f, 0.65f), 1);
	meshList[GEO_PLANET6] = MeshBuilder::GenerateSphere("planet6", Color(0.8f, 1.0f, 0.85f), 1);
	meshList[GEO_PLANET7] = MeshBuilder::GenerateSphere("planet7", Color(0.2f, 0.0f, 0.2f), 1);
	meshList[GEO_PLANET8] = MeshBuilder::GenerateSphere("planet8", Color(0.05f, 0.05f, 0.05f), 1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Scene5::Update(double dt)
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

	
}

void Scene5::Render()
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
		MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		meshList[GEO_AXES]->Render();
	modelStack.PopMatrix();


	modelStack.PushMatrix(); //pushing identity
		modelStack.Translate(0.0f, 0.0f, 0.0f);
		modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
		modelStack.Scale(1.0f, 1.0f, 1.0f);
		MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		meshList[GEO_SUN]->Render();



		modelStack.PushMatrix(); // pushing sphere at origin's model matrix
			modelStack.Rotate(rotateAngle, 0.0f, 1.0f, 0.0f);
			modelStack.Translate(6.0f, 0.0f, 3.0f);  //currently making a copy of identity as it alr pop the axes one earlier
			modelStack.Rotate(0.0f, 0.0f, 0.0f, 1.0f);
			modelStack.Scale(1.0f, 1.0f, 1.0f);
			MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
			meshList[GEO_PLANET1]->Render();



			modelStack.PushMatrix(); // pushing sphere at 3,3,3 that pushed the original sphere at 0,0,0
				modelStack.Rotate(rotateAngle2, 1.0f, 0.0f, 0.0f);
				modelStack.Translate(1.0f, 1.0f, 1.0f);  //currently making a copy of identity as it alr pop the axes one earlier
				modelStack.Rotate(0.0f, 0.0f, 0.0f, 1.0f);
				modelStack.Scale(0.4f, 0.4f, 0.4f);
				MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
				glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
				meshList[GEO_PLANET2]->Render();

			modelStack.PopMatrix();
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Rotate(rotateAngle*1.45, 0.0f, 1.0f, 0.0f);
			modelStack.Translate(13.0f, 1.0f, -3.0f);  //currently making a copy of identity as it alr pop the axes one earlier
			modelStack.Rotate(0.0f, 0.0f, 0.0f, 1.0f);
			modelStack.Scale(1.1f, 1.0f, 1.1f);
			MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
			meshList[GEO_PLANET3]->Render();

		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Rotate(rotateAngle * 0.85, 0.0f, 1.0f, 0.0f);
			modelStack.Translate(16.0f, 1.0f, -9.0f);  //currently making a copy of identity as it alr pop the axes one earlier
			modelStack.Rotate(0.0f, 0.0f, 0.0f, 1.0f);
			modelStack.Scale(1.3f, 1.1f, 1.3f);
			MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
			meshList[GEO_PLANET4]->Render();

			modelStack.PushMatrix();
				modelStack.Rotate(rotateAngle * 1.6, 0.0f, 0.5f, 0.0f);
				modelStack.Translate(1.0f, 1.0f, -0.5f);  //currently making a copy of identity as it alr pop the axes one earlier
				modelStack.Rotate(0.0f, 0.0f, 0.0f, 1.0f);
				modelStack.Scale(0.2f, 0.2f, 0.2f);
				MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
				glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
				meshList[GEO_PLANET5]->Render();
			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Rotate(rotateAngle * 1.6, 0.2f, 0.5f, 0.2f);
				modelStack.Translate(1.0f, -1.0f, 1.0f);  //currently making a copy of identity as it alr pop the axes one earlier
				modelStack.Rotate(0.0f, 0.0f, 0.5f, 1.0f);
				modelStack.Scale(0.2f, 0.2f, 0.2f);
				MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
				glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
				meshList[GEO_PLANET6]->Render();
			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Rotate(rotateAngle * 1.4, 0.5f, 0.2f, 0.2f);
				modelStack.Translate(1.2f, -0.8f, 1.2f);  //currently making a copy of identity as it alr pop the axes one earlier
				modelStack.Rotate(0.0f, 0.3f, 0.5f, 1.0f);
				modelStack.Scale(0.22f, 0.23f, 0.23f);
				MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
				glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
				meshList[GEO_PLANET7]->Render();
			modelStack.PopMatrix();

		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Rotate(rotateAngle * 6, 0.0f, 1.0f, 0.0f);
			modelStack.Translate(18.0f, 1.0f, -19.8f);  //currently making a copy of identity as it alr pop the axes one earlier
			modelStack.Rotate(0.0f, 0.0f, 0.0f, 1.0f);
			modelStack.Scale(1.2f, 1.4f, 1.5f);
			MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
			meshList[GEO_PLANET8]->Render();

			modelStack.PushMatrix();
				modelStack.Rotate(rotateAngle * 8, 0.0f, 1.0f, 1.0f);
				modelStack.Translate(1.0f, 1.0f, -1.0f);  //currently making a copy of identity as it alr pop the axes one earlier
				modelStack.Rotate(20.0f, 1.0f, 0.0f, 1.0f);
				modelStack.Scale(0.2f, 0.2f, 0.2f);
				MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
				glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
				meshList[GEO_PLANET7]->Render();
			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Rotate(rotateAngle * 8, 1.0f, 1.0f, 1.0f);
				modelStack.Translate(0.5f, 0.0f, -1.5f);  //currently making a copy of identity as it alr pop the axes one earlier
				modelStack.Rotate(20.0f, 1.0f, 0.3f, 1.0f);
				modelStack.Scale(0.2f, 0.2f, 0.2f);
				MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
				glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
				meshList[GEO_PLANET7]->Render();
			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Rotate(rotateAngle * 10, 0.2f, 1.0f, 1.0f);
				modelStack.Translate(0.5f, 1.0f, -0.5f);  //currently making a copy of identity as it alr pop the axes one earlier
				modelStack.Rotate(20.0f, 1.0f, 0.0f, 1.0f);
				modelStack.Scale(0.2f, 0.2f, 0.2f);
				MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
				glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
				meshList[GEO_PLANET7]->Render();
			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Rotate(rotateAngle * 8, 1.0f, 1.0f, 1.0f);
				modelStack.Translate(-1.0f, 1.0f, 1.0f);  //currently making a copy of identity as it alr pop the axes one earlier
				modelStack.Rotate(60.0f, 1.0f, 1.0f, 1.0f);
				modelStack.Scale(0.2f, 0.2f, 0.2f);
				MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
				glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
				meshList[GEO_PLANET7]->Render();
			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Rotate(rotateAngle * 12, 1.0f, 1.0f, 0.0f);
				modelStack.Translate(-0.5f, -1.0f, -1.5f);  //currently making a copy of identity as it alr pop the axes one earlier
				modelStack.Rotate(20.0f, 1.0f, 0.0f, 1.0f);
				modelStack.Scale(0.2f, 0.2f, 0.2f);
				MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
				glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
				meshList[GEO_PLANET7]->Render();
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

void Scene5::Exit()
{
	// Cleanup VBO here

	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
