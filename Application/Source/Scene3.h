//#ifndef SCENE_3_H
//#define SCENE_3_H
//
//#include "Scene.h"
//#include <vector>
//#include "../MeshObject.h"
//#include "../Global.h"
//
//class Scene3 : public Scene
//{
//
//enum UNIFORM_TYPE
//{
//	U_MVP = 0,
//	U_TOTAL
//};
//
//private:
//	unsigned m_vertexArrayID;
//	unsigned m_vertexBuffer[NUM_GEOMETRY];
//	unsigned m_colorBuffer[NUM_GEOMETRY];
//	unsigned m_programID;
//
//	//stores handlers for uniform parametes
//	unsigned m_parameters[U_TOTAL];
//
//	std::vector<MeshObject*> toBlackhole;
//	std::vector<MeshObject*> stars;
//
//	int objectEaten;
//	double circleScale;
//	double nextSpawnTime;
//	double restTillTime;
//	int spawnCount;
//	double elapsedTime;
//
//	bool rotateAngleFWD;
//	bool translateXFWD;
//	bool scaleALLFWD;
//	float rotateAngle;
//	float translateX;
//	float scaleAll;
//
//public:
//	Scene3();
//	~Scene3();
//
//	virtual void Init();
//	virtual void Update(double dt);
//	virtual void Render();
//	virtual void Exit();
//};
//
//#endif