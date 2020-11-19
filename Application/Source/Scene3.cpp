// Use full code from Lab 03 practical
//#include "Scene3.h"
//#include "GL\glew.h"
//#include "Mtx44.h"
//
//#include "shader.hpp"
//
//
//Scene3::Scene3()
//{
//	srand(time(NULL));
//	nextSpawnTime = 0;
//	restTillTime = 0;
//	spawnCount = 0;
//	elapsedTime = 0.0;
//	objectEaten = 0;
//	circleScale = 10;
//	for (int i = 0; i < 10; i++) {
//		stars.push_back(new MeshObject(STAR_DEFAULT, 3.0f, 0.0f, rand() % 100 - 50, rand() % 140 - 70, 1.0f, false, true));
//	}
//}
//
//Scene3::~Scene3()
//{
//}
//
//void Scene3::Init()
//{
//	rotateAngle = 0;
//	translateX = 0;
//	scaleAll = 1;
//
//	rotateAngleFWD = true;
//	translateXFWD = true;
//	scaleALLFWD = true;
//
//	// Init VBO here
//	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
//	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
//	glUseProgram(m_programID);
//
//	// Set background color to dark blue
//	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
//
//	// Generate a default VAO for now
//	glGenVertexArrays(1, &m_vertexArrayID);
//	glBindVertexArray(m_vertexArrayID);
//
//	// An array of 3 buffers
//	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
//	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
//
//	// Creating CIRCLE_DEFAULT
//	int range = 60;
//	static GLfloat vertex_buffer_data[180];
//	double pi = atan(1) * 4;
//	for (int i = 1; i <= range; i++) {
//		float degree = (i / 60.0 * 360) * (pi / 180.0);
//		vertex_buffer_data[i*3-3] = 0 + 1.0f * cosf( degree);
//		vertex_buffer_data[i*3-2] = 0 + 1.0f * sinf(degree);
//		vertex_buffer_data[i * 3 - 1] = 0.9f;
//	}
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE_DEFAULT]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
//
//	static GLfloat color_buffer_data[180];
//	for (int i = 0; i < range * 3; i++) {
//		color_buffer_data[i] = 1.0f;
//	}
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CIRCLE_DEFAULT]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
//
//	// Creating CIRCLE_MARS
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE_MARS]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
//
//	float a = (rand() % 1000 / 1000.0);
//	float b = (rand() % 1000 / 1000.0);
//	float c = (rand() % 1000 / 1000.0);
//	for (int i = 0; i < range; i++) {
//		color_buffer_data[i * 3 - 3] = a;
//		color_buffer_data[i * 3 - 2] = b;
//		color_buffer_data[i * 3 - 1] = c;
//	}
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CIRCLE_MARS]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
//
//	
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE_MOON]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
//
//	a = (rand() % 1000 / 1000.0);
//	b = (rand() % 1000 / 1000.0);
//	c = (rand() % 1000 / 1000.0);
//	for (int i = 0; i < range; i++) {
//		color_buffer_data[i * 3 - 3] = a;
//		color_buffer_data[i * 3 - 2] = b;
//		color_buffer_data[i * 3 - 1] = c;
//	}
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CIRCLE_MOON]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
//
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE_SUN]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
//
//	a = (rand() % 1000 / 1000.0);
//	b = (rand() % 1000 / 1000.0);
//	c = (rand() % 1000 / 1000.0);
//	for (int i = 0; i < range; i++) {
//		color_buffer_data[i * 3 - 3] = a;
//		color_buffer_data[i * 3 - 2] = b;
//		color_buffer_data[i * 3 - 1] = c;
//	}
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CIRCLE_SUN]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE_GREYLANDS]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
//
//	a = (rand() % 1000 / 1000.0);
//	b = (rand() % 1000 / 1000.0);
//	c = (rand() % 1000 / 1000.0);
//	for (int i = 0; i < range; i++) {
//		color_buffer_data[i * 3 - 3] = a;
//		color_buffer_data[i * 3 - 2] = b;
//		color_buffer_data[i * 3 - 1] = c;
//	}
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CIRCLE_GREYLANDS]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
//
//	// Creating ARC_DEFAULT
//	range = 10;
//	static GLfloat vertex_buffer_data5[30];
//	for (int i = 1; i <= range; i++) {
//		float degree = (i / 60.0 * 360) * (pi / 180.0);
//		vertex_buffer_data5[i * 3 - 3] = 0.2f + 1.0f * cosf(degree);
//		vertex_buffer_data5[i * 3 - 2] = 0.2f + 1.0f * sinf(degree);
//		vertex_buffer_data5[i * 3 - 1] = 1.0f;
//	}
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[ARC_DEFAULT]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data5), vertex_buffer_data5, GL_STATIC_DRAW);
//
//	static GLfloat color_buffer_data5[180];
//	for (int i = 0; i < range * 3; i++) {
//		color_buffer_data5[i] = 1.0f;
//	}
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[ARC_DEFAULT]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data5), color_buffer_data5, GL_STATIC_DRAW);
//
//	// Creating ARC_WIDE
//	range = 15;
//	static GLfloat vertex_buffer_data6[30];
//	for (int i = 1; i <= range; i++) {
//		float degree = (i / 60.0 * 360) * (pi / 180.0);
//		vertex_buffer_data6[i * 3 - 3] = 0.5f + 1.0f * cosf(degree);
//		vertex_buffer_data6[i * 3 - 2] = 0.5f + 1.0f * sinf(degree);
//		vertex_buffer_data6[i * 3 - 1] = 1.0f;
//	}
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[ARC_WIDE]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data6), vertex_buffer_data6, GL_STATIC_DRAW);
//
//	static GLfloat color_buffer_data6[180];
//	for (int i = 0; i < range * 3; i++) {
//		color_buffer_data6[i] = 1.0f;
//	}
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[ARC_WIDE]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data6), color_buffer_data6, GL_STATIC_DRAW);
//
//
//	// Square
//	static const GLfloat vertex_buffer_data2[] = {
//		1.0f, 1.0f, 1.1f,
//		-1.0f, 1.0f, 1.1f,
//		-1.0f, -1.0f, 1.1f,
//		1.0f, -1.0f, 1.1f,
//	};
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[SQUARE_DEFAULT]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);
//	static const GLfloat color_buffer_data2[] = {
//		0.01f, 0.01f, 0.01f,
//		0.01f, 0.01f, 0.01f,
//		0.01f, 0.01f, 0.01f,
//		0.01f, 0.01f, 0.01f,
//	};
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[SQUARE_DEFAULT]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data2), color_buffer_data2, GL_STATIC_DRAW);
//
//	// Triangle
//	static const GLfloat vertex_buffer_data3[] = {
//		-1.0f, 1.0f, 1.0f,
//		-1.0f, -1.0f, 1.0f,
//		1.0f, -1.0f, 1.0f,
//	};
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TRIANGLE_RIGHT_ANGLE]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data3), vertex_buffer_data3, GL_STATIC_DRAW);
//	static const GLfloat color_buffer_data3[] = {
//		1.0f, 1.0f, 0.0f,
//		1.0f, 1.0f, 0.0f,
//		1.0f, 1.0f, 0.0f,
//	};
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TRIANGLE_RIGHT_ANGLE]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data3), color_buffer_data3, GL_STATIC_DRAW);
//
//	//Star
//	static const GLfloat vertex_buffer_data4[] = {
//	0.0f, 0.35f, 1.0f, //v
//	-0.2f, -0.35f, 1.0f, //l
//	0.0f, -0.15f, 1.0f, //z tip of 5-sided polygon
//
//	0.0f, 0.35f, 1.0f, //v
//	0.2f, -0.35f, 1.0f, //h
//	0.0f, -0.15f, 1.0f, //z tip of 5-sided polygon
//
//	-0.3f, 0.1f, 1.0f, //y
//	0.3f, 0.1f, 1.0f, //alpha
//	0.0f, -0.15f, 1.0f, //z tip of 5-sided polygon
//	};
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR_DEFAULT]); //vertex
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data4), vertex_buffer_data4, GL_STATIC_DRAW);
//	static const GLfloat color_buffer_data4[] = {
//		1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f,
//	};
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR_DEFAULT]); //color
//	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data4), color_buffer_data4, GL_STATIC_DRAW);
//
//
//
//	glEnable(GL_DEPTH_TEST);
//}
//
//void Scene3::Update(double dt)
//{
//	elapsedTime += dt;
//	if (elapsedTime > restTillTime && elapsedTime > nextSpawnTime) {
//		nextSpawnTime = elapsedTime + 2.0;
//		if (++spawnCount >= 10) {
//			restTillTime = elapsedTime + 10.0;
//			spawnCount = 0;
//		}
//		//adding obj
//		int x = rand() % 20 + circleScale + 25;
//		if (rand() % 2 == 0) x = -x;
//		int y = rand() % 140 - 70;
//		
//		SCENE_3_GEOMETRY_TYPE type;
//
//		switch (rand() % 6) {
//		case 0:
//			type = CIRCLE_DEFAULT;
//			break;
//		case 1:
//			type = CIRCLE_GREYLANDS;
//			break;
//		case 2:
//			type = CIRCLE_MARS;
//			break;
//		case 3:
//			type = CIRCLE_MOON;
//			break;
//		case 4:
//			type = CIRCLE_SUN;
//			break;
//		case 5:
//			type = STAR_DEFAULT;
//			break;
//		}
//		toBlackhole.push_back(new MeshObject(type, rand() % 15 + 12, 0.0f, x, y, 1.0f, false, true));
//	}
//
//
//	std::vector<int> indexesToRemove;
//	int i = 0;
//	for (auto& meshObj : toBlackhole) {
//		if (meshObj->getScale() < 0) {
//			indexesToRemove.push_back(i);
//			objectEaten++;
//			circleScale += 0.2 + objectEaten / 50.0;
//			continue;
//		}
//		meshObj->setRotation(meshObj->getRotation() + 1);
//		float newX = meshObj->getTransX();
//		float newY = meshObj->getTransY();
//		if (newX > 0.0) {
//			newX -= 1.0;
//			if (newX < 0.0) newX = 0.0;
//			meshObj->setTransX(newX);
//		}else if (newX < 0) {
//			newX += 1;
//			if (newX > 0) newX = 0;
//			meshObj->setTransX(newX);
//		}
//		double diff = ((newY < 0 ? -newY : newY) / (newX < 0? -newX : newX));
//		//if(newY < newX) diff = (newX / (newY < 0 ? -newY : newY));
//		if (newY > 0) {
//			newY -= 1.0 * diff;
//			if (newY < 0) newY = 0;
//			meshObj->setTransY(newY);
//		}
//		else if (newY < 0) {
//			newY += 1.0 * diff;
//			if (newY > 0) newY = 0;
//			meshObj->setTransY(newY);
//		}
//		if (newX == 0 && newY == 0) {
//			meshObj->setScale(meshObj->getScale() - 1);
//		}
//		i++;
//	}
//	if (indexesToRemove.size() > 0) {
//		for (int i = indexesToRemove.size() - 1; i >= 0; i--) {
//			toBlackhole.erase(toBlackhole.begin() + indexesToRemove.at(i));
//		}
//	}
//
//	for (auto& element : stars) {
//		element->setRotation(element->getRotation() + (rand() % 20 + 220)/100.0);
//	}
//
//	if (rotateAngleFWD) {
//		rotateAngle += 1;
//	}
//
//
//
//	if (translateXFWD) {
//		translateX += 2;
//		if (translateX >= 80) {
//			translateXFWD = false;
//		}
//	}
//	else {
//		translateX -= 2;
//		if (translateX <= -80) {
//			translateXFWD = true;
//		}
//	}
//
//	if (scaleALLFWD) {
//		scaleAll += 1;
//		if (scaleAll >= 40)
//			scaleALLFWD = false;
//	}
//	else {
//		scaleAll -= 1;
//		if (scaleAll <= -30)
//			scaleALLFWD = true;
//	}
//}
//
//void Scene3::Render()
//{
//
//	glEnableVertexAttribArray(0); // 1st attribute buffer: vertices
//	glEnableVertexAttribArray(1); // 2nd attribute buffer: color
//
//	// Render VBO here
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	Mtx44 translate, rotate, scale;
//	Mtx44 model;
//	Mtx44 view;
//	Mtx44 projection;
//	Mtx44 MVP;
//
//	/* First Triangle
//	*/
//
//	//Safe to initialize values as identity matrix (not a zero matrix!)
//	view.SetToIdentity(); //no need camera matrix, set to origin
//	projection.SetToOrtho(-50.0, 50.0, -70.0, 70.0, -10.0, 10.0);
//
//	for (auto& meshObj : stars) {
//		translate.SetToIdentity();
//		rotate.SetToIdentity();
//		scale.SetToIdentity();
//
//		scale.SetToScale(meshObj->getScale(), meshObj->getScale(), 0.2f);
//		rotate.SetToRotation(meshObj->getRotation(), 0.0f, 0.0f, 1.0f);
//		translate.SetToTranslation(meshObj->getTransX(), meshObj->getTransY(), meshObj->getTransZ());
//		model = translate * rotate * scale;
//		MVP = projection * view * model;
//		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//
//		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[meshObj->getType()]);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[meshObj->getType()]);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//		switch (meshObj->getType()) {
//		case CIRCLE_DEFAULT:
//		case CIRCLE_MARS:
//		case CIRCLE_SUN:
//		case CIRCLE_GREYLANDS:
//		case CIRCLE_MOON:
//			glDrawArrays(GL_TRIANGLE_FAN, 0, 180);
//			break;
//		case ARC_DEFAULT:
//			glDrawArrays(GL_LINES, 0, 180);
//			break;
//		case ARC_WIDE:
//			glDrawArrays(GL_LINES, 0, 180);
//			break;
//		case SQUARE_DEFAULT:
//			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
//			break;
//		case TRIANGLE_RIGHT_ANGLE:
//			glDrawArrays(GL_TRIANGLES, 0, 3);
//			break;
//		case STAR_DEFAULT:
//			glDrawArrays(GL_TRIANGLES, 0, 9);
//			break;
//
//		}
//	}
//
//	for (auto& meshObj : toBlackhole) {
//		translate.SetToIdentity();
//		rotate.SetToIdentity();
//		scale.SetToIdentity();
//
//		scale.SetToScale(meshObj->getScale(), meshObj->getScale(), 1.0f);
//		rotate.SetToRotation(meshObj->getRotation(), 0.0f, 0.0f, 1.0f);
//		translate.SetToTranslation(meshObj->getTransX(), meshObj->getTransY(), meshObj->getTransZ());
//		model = translate * rotate * scale;
//		MVP = projection * view * model;
//		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//
//		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[meshObj->getType()]);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[meshObj->getType()]);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//		
//		switch (meshObj->getType()) {
//		case CIRCLE_DEFAULT:
//		case CIRCLE_MARS:
//		case CIRCLE_SUN:
//		case CIRCLE_GREYLANDS:
//		case CIRCLE_MOON:
//			glDrawArrays(GL_TRIANGLE_FAN, 0, 180);
//			break;
//		case ARC_DEFAULT:
//			glDrawArrays(GL_LINES, 0, 180);
//			break;
//		case ARC_WIDE:
//			glDrawArrays(GL_LINES, 0, 180);
//			break;
//		case SQUARE_DEFAULT:
//			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
//			break;
//		case TRIANGLE_RIGHT_ANGLE:
//			glDrawArrays(GL_TRIANGLES, 0, 3);
//			break;
//		case STAR_DEFAULT:
//			glDrawArrays(GL_TRIANGLES, 0, 9);
//			break;
//
//		}
//	}
//	
//	translate.SetToIdentity();
//	rotate.SetToIdentity();
//	scale.SetToIdentity();
//
//	scale.SetToScale(circleScale, circleScale, 9.0f);
//	rotate.SetToRotation(rotateAngle*4, 0.0f, 0.0f, 1.0f);
//	translate.SetToTranslation(0, 0, 0.0);
//	model = translate * rotate * scale;
//	MVP = projection * view * model;
//
//	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE_DEFAULT]);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CIRCLE_DEFAULT]);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glDrawArrays(GL_TRIANGLE_FAN, 0, 180);
//
//	//Arc
//	translate.SetToIdentity();
//	rotate.SetToIdentity();
//	scale.SetToIdentity();
//
//	scale.SetToScale(circleScale, circleScale, 10);
//	rotate.SetToRotation(rotateAngle * 3.2, 0.0f, 0.0f, 1.0f);
//	translate.SetToTranslation(0, 0, 0.0);
//	model = translate * rotate * scale;
//	MVP = projection * view * model;
//
//	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[ARC_DEFAULT]);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[ARC_DEFAULT]);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glDrawArrays(GL_LINES, 0, 180);
//
//
//	//Arc 2
//	translate.SetToIdentity();
//	rotate.SetToIdentity();
//	scale.SetToIdentity();
//
//	scale.SetToScale(circleScale, circleScale, 9.0f);
//	rotate.SetToRotation(rotateAngle * 3.2 - 180, 0.0f, 0.0f, 1.0f);
//	translate.SetToTranslation(0, 0, 0.0);
//	model = translate * rotate * scale;
//	MVP = projection * view * model;
//
//	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[ARC_DEFAULT]);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[ARC_DEFAULT]);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glDrawArrays(GL_LINES, 0, 180);
//
//	//Arc_WIDE 1
//	translate.SetToIdentity();
//	rotate.SetToIdentity();
//	scale.SetToIdentity();
//
//	scale.SetToScale(circleScale, circleScale, 9.0f);
//	rotate.SetToRotation(rotateAngle * 5, 0.0f, 0.0f, 1.0f);
//	translate.SetToTranslation(0, 0, 0.0);
//	model = translate * rotate * scale;
//	MVP = projection * view * model;
//
//	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[ARC_WIDE]);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[ARC_WIDE]);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glDrawArrays(GL_LINES, 0, 180);
//
//	//Arc_WIDE 2
//	translate.SetToIdentity();
//	rotate.SetToIdentity();
//	scale.SetToIdentity();
//
//	scale.SetToScale(circleScale, circleScale, 9.0f);
//	rotate.SetToRotation(rotateAngle * 5 - 90, 0.0f, 0.0f, 1.0f);
//	translate.SetToTranslation(0, 0, 0.0);
//	model = translate * rotate * scale;
//	MVP = projection * view * model;
//
//	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[ARC_WIDE]);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[ARC_WIDE]);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glDrawArrays(GL_LINES, 0, 180);
//
//	//Arc_WIDE 3
//	translate.SetToIdentity();
//	rotate.SetToIdentity();
//	scale.SetToIdentity();
//
//	scale.SetToScale(circleScale, circleScale, 9.0f);
//	rotate.SetToRotation(rotateAngle * 5 - 180, 0.0f, 0.0f, 1.0f);
//	translate.SetToTranslation(0, 0, 0.0);
//	model = translate * rotate * scale;
//	MVP = projection * view * model;
//
//	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[ARC_WIDE]);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[ARC_WIDE]);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glDrawArrays(GL_LINES, 0, 180);
//
//	//Arc_WIDE 4
//	translate.SetToIdentity();
//	rotate.SetToIdentity();
//	scale.SetToIdentity();
//
//	scale.SetToScale(circleScale, circleScale, 9.0f);
//	rotate.SetToRotation(rotateAngle * 5 - 270, 0.0f, 0.0f, 1.0f);
//	translate.SetToTranslation(0, 0, 0.0);
//	model = translate * rotate * scale;
//	MVP = projection * view * model;
//
//	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[ARC_WIDE]);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[ARC_WIDE]);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glDrawArrays(GL_LINES, 0, 180);
//
//	/* Sqaure
//	*/
//	translate.SetToIdentity();
//	rotate.SetToIdentity();
//	scale.SetToIdentity();
//
//	scale.SetToScale(50, 70, 0.1);
//	rotate.SetToRotation(0, 0.0f, 0.0f, 1.0f);
//	translate.SetToTranslation(0, 0, 1.0);
//	model = translate * rotate * scale;
//	MVP = projection * view * model;
//
//	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[SQUARE_DEFAULT]);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[SQUARE_DEFAULT]);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
//
//	/* RIGHT_ANGLE_TRIANGLE
//	*/
//	/*translate.SetToIdentity();
//	rotate.SetToIdentity();
//	scale.SetToIdentity();
//
//	scale.SetToScale(10.0f, 10.0f, 10.0f);
//	rotate.SetToRotation(0, 0.0f, 0.0f, 1.0f);
//	translate.SetToTranslation(45, 45, 0.0);
//	model = translate * rotate * scale;
//	MVP = projection * view * model;
//
//	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TRIANGLE_RIGHT_ANGLE]);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TRIANGLE_RIGHT_ANGLE]);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glDrawArrays(GL_TRIANGLES, 0, 3);*/
//
//	/* STAR
//	*/
//	//translate.SetToIdentity();
//	//rotate.SetToIdentity();
//	//scale.SetToIdentity();
//
//	//scale.SetToScale(13.0f, 13.0f, 10.0f);
//	//rotate.SetToRotation(rotateAngle, 0.0f, 0.0f, 1.0f);
//	//translate.SetToTranslation(-45, -45, 0.0);
//	//model = translate * rotate * scale;
//	//MVP = projection * view * model;
//
//	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//
//	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR_DEFAULT]);
//	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR_DEFAULT]);
//	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	//glDrawArrays(GL_TRIANGLES, 0, 9);
//
//	/* Third Triangle
//	*/
//
//	/*translate.SetToIdentity();
//	rotate.SetToIdentity();
//	scale.SetToIdentity();
//
//	scale.SetToScale(6, 6, 6);
//	rotate.SetToRotation(rotateAngle-40, 0.0f, 0.0f, 1.0f);
//	translate.SetToTranslation(translateX, 50, 0.0);
//	model = translate * rotate * scale;
//	MVP = projection * view * model;
//
//	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glDrawArrays(GL_TRIANGLES, 0, 3);*/
//
//	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//
//	/*glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glDrawArrays(GL_TRIANGLES, 0, 3);*/
//}
//
//void Scene3::Exit()
//{
//	// Cleanup VBO here
//	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
//	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
//	glDeleteVertexArrays(1, &m_vertexArrayID);
//	glDeleteProgram(m_programID);
//
//	for (auto& obj : toBlackhole) {
//		delete obj;
//	}
//	for (auto& obj : stars) {
//		delete obj;
//	}
//}
