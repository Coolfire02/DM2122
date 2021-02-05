#pragma once

#include "MeshHandler.h"
#include "HitBox.h"
#include "EntityDataHandler.h"
#include "Scene.h"
//#include <map>

enum ENTITYTYPE {
	SONIC,
	COIN,
	FENCE,
	EGGMAN,
	CLOUD,
	SPOTLIGHT,
	FINISHLINE,
};

class Entity 
{
protected:
	Scene *scene;
	bool dead;
	ENTITYTYPE type;
	EntityData data;
	HitBox hitBox; //Gets updated based on Position, defaultMin and defaultMax scaled on scale.
	//Side note, if u want to calculate hitboxes with multiple "Boxes" u can do it in construct of Entity sub-types when u specify the geometries you plan to use.
	
	//std::multimap<GEOMETRY_TYPE, EntityMeshData*>(); ? why do u need this wtf comment out

public:
	Entity(Scene* associatedScene, ENTITYTYPE type);
	~Entity();

	bool isDead();
	EntityData getLocation();
	HitBox getHitBox();

	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
};

