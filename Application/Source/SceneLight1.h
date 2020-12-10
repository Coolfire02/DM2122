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

	U_LIGHT0_TYPE,
	U_LIGHT0_SPOTDIRECTION,
	U_LIGHT0_COSCUTOFF,
	U_LIGHT0_COSINNER,
	U_LIGHT0_EXPONENT,
	U_NUMLIGHTS,

	U_TOTAL,
};

enum GEOMETRY_TYPE
{
	GEO_GRASS = 0,
	GEO_DIRT,
	GEO_AXES,
	GEO_SONICHEAD,
	GEO_SONICEYEBALL,
	GEO_SONICGREENEYE,
	GEO_SONICBLACKEYE,
	GEO_SONICEARS,
	GEO_INNERSONICEARS,
	GEO_MOUTHTORUS,
	GEO_MOUTHSPHERE,

	GEO_NOSE_HEMISPHERE,

	GEO_HAIRHEMISPHERE,
	GEO_HAIRHEMISPHEREFRUSTUM,
	GEO_HAIRCONE,
	GEO_HAIRHALFCONE,
	GEO_HAIRCONICALFRUSTUM,

	GEO_BODY_BACK_HEMISPHERE,
	GEO_BODY_FRONT_BLUE_HEMISPHERE_FRUSTUM,
	GEO_BODY_FRONT_ORANGE_HEMISPHERE,

	GEO_ARMCYLINDER,
	GEO_ARMHEMISPHERE,
	GEO_ARMSPHERE,
	GEO_HANDTORUS,
	GEO_HANDCYLINDER,
	GEO_HANDHEMISPHERE,

	GEO_LEGCYLINDER,
	GEO_LEGTORUS,
	GEO_LEGHEMISPHERE,
	GEO_LEGSPHERE,

	GEO_BOOTSQUATERSPHERE,
	GEO_BOOTSLACEHALFTORUS,
	GEO_BOOTSFEETTORUS,
	GEO_BOOTSLACEHOOK,

	GEO_LIGHTBALL,
	NUM_GEOMETRY,
};

enum DIRECTION {
	LEFT = -1,
	RIGHT = 1,
};

enum ANIMATION {
	WALK,
	RUN,
	RUNJUMP,
	NO_ANIMATION,
};

enum ANIMATION_OFFSET {
	BODY_TILT = 0,
	HEAD_TILT,

	LEFT_ARM_ELBOW_PITCH,
	LEFT_ARM_ELBOW_ROLL,
	LEFT_ARM_SHOULDER_YAW,
	LEFT_ARM_SHOULDER_PITCH,
	
	RIGHT_ARM_ELBOW_PITCH,
	RIGHT_ARM_ELBOW_ROLL,
	RIGHT_ARM_SHOULDER_YAW,
	RIGHT_ARM_SHOULDER_PITCH,
	
	LEFT_LEG_ORIGIN_PITCH,
	RIGHT_LEG_ORIGIN_PITCH,
	
	LEFT_LEG_KNEE_TILT,
	RIGHT_LEG_KNEE_TILT,
	
	ANIMATION_TOTAL
};

private:

	Camera2 camera;

	unsigned m_vertexArrayID;
	unsigned m_programID;

	//stores handlers for uniform parametes
	unsigned m_parameters[U_TOTAL];

	double animation_offset[ANIMATION_TOTAL];

	Mesh* meshList[NUM_GEOMETRY];
	Light light[1];
	MS modelStack, viewStack, projectionStack;

	//Animation
	double startAnimation;
	double endAnimation;
	int stackedAnimations;
	ANIMATION currentAnimation;
	
	double elapsed;
	bool rotateAngleFWD;
	bool translateZFWD;
	bool scaleALLFWD;
	float rotateAngle;
	float rotateAngle2;
	float translateZ;
	float scaleAll;

	void RenderMesh(Mesh* mesh, bool lightEnabled);
	void animationUpdater(double dt);
	void resetAnimation();
	void processAnimation(double aniTime, double animationStart, double animationLength, float degreeTilt, ANIMATION_OFFSET type);

public:
	SceneLight1();
	~SceneLight1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif