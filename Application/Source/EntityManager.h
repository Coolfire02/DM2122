#pragma once
#include "Entity.h"
#include <vector>
#include "Scene.h"

struct CollidedWith {
	const Entity* attacker, * victim;
	CollidedWith(Entity* attacker, Entity* victim) : attacker(attacker), victim(victim) {};
};

class EntityManager
{
	const Scene* scene; //World all entities are in;
	std::vector<Entity*> worldEntities;
	std::vector<Entity*> movingEntities; //Moving entities, generally just Players for now (Sonic)

public:
	EntityManager(Scene* scene);
	~EntityManager();
	
	void spawnMovingEntity(Entity*);
	void spawnWorldEntity(Entity*);

	void preCollisionUpdate(); // serves no purpose atm, but may in the future.
	std::vector<CollidedWith> collisionUpdate(double dt); //Updates whether objects are dead here
	void postCollisionUpdate(); //Clears up dead entities (Remove from list, clear pointers)

	std::vector<Entity*>& getEntites();
};

