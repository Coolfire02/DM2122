#ifndef SCENE_LIGHT1_H
#define SCENE_LIGHT1_H

#include "Scene.h"
#include "Camera2.h"	
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"

class SceneLight1 : public Scene
{

enum UNIFORM_TYPE
{
	U_MVP = 0,
	U_MODELVIEW,
	U_MODELVIEW_INVERSE_TRANSPOSE,
	U_MATERIAL_AMBIENT,
	U_MATERIAL_DIFFUSE,
	U_MATERIAL_SPECULAR,
	U_MATERIAL_SHININESS,
	U_LIGHT0_POSITION,
	U_LIGHT0_COLOR,
	U_LIGHT0_POWER,
	U_LIGHT0_KC,
	U_LIGHT0_KL,
	U_LIGHT0_KQ,
	U_LIGHTENABLED,
	U_TOTAL,
};

enum GEOMETRY_TYPE
{
	GEO_CUBE = 0,
	GEO_AXES,
	GEO_SONICHEAD,
	GEO_SONICEYEBALL,
	GEO_SONICGREENEYE,
	GEO_SONICBLACKEYE,
	GEO_SONICEARS,
	GEO_INNERSONICEARS,
	GEO_MOUTHTORUS,
	GEO_MOUTHSPHERE,

	GEO_HAIRHEMISPHERE,
	GEO_HAIRCONE,
	GEO_HAIRHALFCONE,

	GEO_LIGHTBALL,
	NUM_GEOMETRY,
};

private:

	Camera2 camera;

	unsigned m_vertexArrayID;
	unsigned m_programID;

	//stores handlers for uniform parametes
	unsigned m_parameters[U_TOTAL];

	Mesh* meshList[NUM_GEOMETRY];
	Light light[1];
	MS modelStack, viewStack, projectionStack;

	bool rotateAngleFWD;
	bool translateZFWD;
	bool scaleALLFWD;
	float rotateAngle;
	float rotateAngle2;
	float translateZ;
	float scaleAll;

	void RenderMesh(Mesh* mesh, bool lightEnabled);

public:
	SceneLight1();
	~SceneLight1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif