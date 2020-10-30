#include "Scene2.h"
#include "GL\glew.h"
#include "Mtx44.h"

#include "shader.hpp"


Scene2::Scene2()
{
}

Scene2::~Scene2()
{
}

void Scene2::Init()
{
	rotateAngle = 0;
	translateX = 0;
	scaleAll = 1;

	rotateAngleFWD = true;
	translateXFWD = true;
	scaleALLFWD = true;

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
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data[] = {
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.35f, 0.0f,
		0.5f, -0.35f, 0.0f,
	};

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);

	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);


	// 2nd Triangle
	//static const GLfloat vertex_buffer_data2[] = {
	//	0.0f, 0.0f, 0.5f, //vertex 0 of triangle
	//	1.0f, -1.0f, 0.5f, //vertex 1 of triangle
	//	1.0f, 1.0f, 0.5f //vertex 2 of triangle
	//};

	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);

	//static const GLfloat color_buffer_data2[] = {
	//	1.0f, 1.0f, 0.0f,
	//	1.0f, 1.0f, 0.0f,
	//	1.0f, 1.0f, 0.0f
	//};

	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data2), color_buffer_data2, GL_STATIC_DRAW);

	glEnable(GL_DEPTH_TEST);
}

void Scene2::Update(double dt)
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

	if (translateXFWD) {
		translateX += 2;
		if (translateX >= 80) {
			translateXFWD = false;
		}
	}
	else {
		translateX -= 2;
		if (translateX <= -80) {
			translateXFWD = true;
		}
	}

	if (scaleALLFWD) {
		scaleAll += 1;
		if (scaleAll >= 30)
			scaleALLFWD = false;
	}
	else {
		scaleAll -= 1;
		if (scaleAll <= -30)
			scaleALLFWD = true;
	}
}

void Scene2::Render()
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
	view.SetToIdentity(); //no need camera matrix, set to origin
	projection.SetToOrtho(-80.0, 80.0, -60.0, 60.0, -10.0, 10.0);
	
	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();

	scale.SetToScale(10, 10, 10);
	rotate.SetToRotation(rotateAngle*4, 0.0f, 0.0f, 1.0f);
	translate.SetToTranslation(0, 0, 0.0);
	model = translate * rotate * scale;
	MVP = projection * view * model;

	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	/* Second Triangle
	*/
	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();

	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	rotate.SetToRotation(40, 0.0f, 0.0f, 1.0f);
	translate.SetToTranslation(30, 30, 0.0);
	model = translate * rotate * scale;
	MVP = projection * view * model;

	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	/* Third Triangle
	*/

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();

	scale.SetToScale(6, 6, 6);
	rotate.SetToRotation(rotateAngle-40, 0.0f, 0.0f, 1.0f);
	translate.SetToTranslation(translateX, 50, 0.0);
	model = translate * rotate * scale;
	MVP = projection * view * model;

	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	/*glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);*/
}

void Scene2::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
