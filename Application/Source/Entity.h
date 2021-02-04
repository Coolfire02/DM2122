#pragma once

#include "MeshHandler.h"
#include "HitBox.h"
#include "EntityDataHandler.h"
//#include <map>

enum ENTITYTYPE {
	PLAYER,
	COIN,
	FENCE,
	EGGMAN,
	CLOUD,
	SPOTLIGHT,
	FINISHLINE,
};

class Entity
{
	ENTITYTYPE type;
	EntityData data;
	HitBox hitBox; //Gets updated based on Position, defaultMin and defaultMax scaled on scale.
	//Side note, if u want to calculate hitboxes with multiple "Boxes" u can do it in construct of Entity sub-types when u specify the geometries you plan to use.
	
	//std::multimap<GEOMETRY_TYPE, EntityMeshData*>(); ? why do u need this wtf comment out

	bool dead;

public:

	static bool loadedGeometries;
	static bool loadGeometries();

	Entity();
	~Entity();
	bool isDead();
	virtual void Render() = 0;
};

