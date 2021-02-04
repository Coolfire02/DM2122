#ifndef SCENE_UI1_H
#define SCENE_UI1_H

#include "Scene.h"
#include "FirstPersonCamera.h"	
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"

class SceneUI : public Scene
{

	enum GEOMETRY_TYPE
	{
		GEO_AXES = 0,

		//Week 14
		GEO_TEXT,

		GEO_MODEL1,
		GEO_MODEL2,
		GEO_MODEL3,
		GEO_MODEL4,
		GEO_MODEL5,
		GEO_MODEL6,

		GEO_SKY_LEFT,
		GEO_SKY_RIGHT,
		GEO_SKY_TOP,
		GEO_SKY_BOTTOM,
		GEO_SKY_FRONT,
		GEO_SKY_BACK,

		GEO_ICON,

		GEO_SONIC_AMY,

		GEO_LIGHTBALL,
		NUM_GEOMETRY,
	};

private:

	FirstPersonCamera camera;

	Mesh* meshList[NUM_GEOMETRY];
	Light light[2];
	//MS modelStack, viewStack, projectionStack;
	bool lightEnable;
	bool rotateAngleFWD;
	bool translateZFWD;
	bool scaleALLFWD;
	float rotateAngle;
	float rotateAngle2;
	float translateZ;
	float scaleAll;

	float fps;
	void RenderSkybox();


public:
	SceneUI();
	~SceneUI();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif