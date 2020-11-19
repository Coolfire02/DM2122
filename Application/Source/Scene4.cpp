#include "Scene4.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include <Windows.h>

#include "shader.hpp"


Scene4::Scene4()
{
	rotateAngle = 0;
	translateX = 0;
	scaleAll = 1;

	rotateAngleFWD = true;
	translateXFWD = true;
	scaleALLFWD = true;
}

Scene4::~Scene4()
{
}

void Scene4::Init() {

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

	//Camera init(starting pos, where it looks at, up
	camera.Init(Vector3(4, 3, 3), Vector3(0,0,0), Vector3(0,1,0));

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", 1, 1, 1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Scene4::Update(double dt)
{
	if (rotateAngleFWD) {
		rotateAngle += 1;
		if (rotateAngle >= 360)
			rotateAngleFWD = false;
	}
	else {
		rotateAngle -= 1;
		if (rotateAngle <= -360)
			rotateAngleFWD = true;
	}
	if (GetKeyState('1') & 0x8000) {
		glEnable(GL_CULL_FACE);
	}
	else if (GetKeyState('2') & 0x8000) {
		glDisable(GL_CULL_FACE);
	}
	else if (GetKeyState('3') & 0x8000) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if (GetKeyState('4') & 0x8000) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	
}

void Scene4::Render()
{

	glEnableVertexAttribArray(0); // 1st attribute buffer: vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer: color

	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;

	/* First Triangle
	*/

	//Safe to initialize values as identity matrix (not a zero matrix!)
	//view.SetToIdentity(); //no need camera matrix, set to origin
	//projection.SetToOrtho(-80.0, 80.0, -60.0, 60.0, -10.0, 10.0);

	view.SetToLookAt(camera.position.x, camera.position.y, camera.position.z, 
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	projection.SetToPerspective(45.0f, 8.0f/6.0f, 0.1f, 1000.0f);
	
	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();

	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(rotateAngle, 0.0f, 0.0f, 1.0f);
	translate.SetToTranslation(0, 0, 0.0);
	model = translate * rotate * scale;
	MVP = projection * view * model;

	meshList[GEO_CUBE]->Render();

	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	
}

void Scene4::Exit()
{
	// Cleanup VBO here

	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
