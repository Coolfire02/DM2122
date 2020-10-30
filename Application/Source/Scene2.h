#ifndef SCENE_2_H
#define SCENE_2_H

#include "Scene.h"

class Scene2 : public Scene
{

enum UNIFORM_TYPE
{
	U_MVP = 0,
	U_TOTAL
};

enum GEOMETRY_TYPE
{
	GEO_TRIANGLE_1 = 0,
	GEO_TRIANGLE_2,
	NUM_GEOMETRY,
};

private:
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;

	//stores handlers for uniform parametes
	unsigned m_parameters[U_TOTAL];

	bool rotateAngleFWD;
	bool translateXFWD;
	bool scaleALLFWD;
	float rotateAngle;
	float translateX;
	float scaleAll;

public:
	Scene2();
	~Scene2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif