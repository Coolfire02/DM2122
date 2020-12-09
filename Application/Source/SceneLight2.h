#ifndef SCENE_LIGHT2_H
#define SCENE_LIGHT2_H

#include "Scene.h"
#include "Camera2.h"	
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"

class SceneLight2 : public Scene
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

	//week 7
	U_LIGHT0_TYPE,
	U_LIGHT0_SPOTDIRECTION,
	U_LIGHT0_COSCUTOFF,
	U_LIGHT0_COSINNER,
	U_LIGHT0_EXPONENT,

	U_LIGHT1_POSITION,
	U_LIGHT1_COLOR,
	U_LIGHT1_POWER,
	U_LIGHT1_KC,
	U_LIGHT1_KL,
	U_LIGHT1_KQ,
	U_LIGHT1_TYPE,
	U_LIGHT1_SPOTDIRECTION,
	U_LIGHT1_COSCUTOFF,
	U_LIGHT1_COSINNER,
	U_LIGHT1_EXPONENT,

	U_LIGHTENABLED,
	U_NUMLIGHTS,

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
	GEO_HAIRHEMISPHEREFRUSTUM,
	GEO_HAIRCONE,
	GEO_HAIRHALFCONE,
	GEO_HAIRCONICALFRUSTUM,

	GEO_ARMCYLINDER,
	GEO_ARMHEMISPHERE,
	GEO_HANDTORUS,
	GEO_HANDCYLINDER,
	GEO_HANDHEMISPHERE,

	GEO_LEGCYLINDER,
	GEO_LEGTORUS,
	GEO_LEGHEMISPHERE,
	GEO_LEGSPHERE,

	GEO_BOOTSQUATERSPHERE,
	GEO_BOOTSLACETORUS,
	GEO_BOOTSFEETTORUS,
	GEO_BOOTSLACEHOOK,

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
	Light light[2];
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
	SceneLight2();
	~SceneLight2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif