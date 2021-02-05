#pragma once
#include "Entity.h"
#include <vector>
#include "Scene.h"

struct CollidedWith {
	const Entity* attacker, * victim;
	const bool justCollided;
	CollidedWith(Entity* attacker, Entity* victim, bool justCollided) : attacker(attacker), victim(victim), justCollided(justCollided) {};
};

class EntityManager
{
	const Scene* scene; //World all entities are in;
	std::vector<Entity*> worldEntities;
	std::vector<Entity*> movingEntities; //Moving entities, generally just Players for now (Sonic)

	std::vector<CollidedWith*> prevTick;
	std::vector<CollidedWith*> thisTick;

public:
	EntityManager(Scene* scene);
	~EntityManager();
	
	void spawnMovingEntity(Entity*);
	void spawnWorldEntity(Entity*);

	std::vector<CollidedWith*> preCollisionUpdate(); // serves no purpose atm, but may in the future.
	void collisionUpdate(double dt); //Updates whether objects are dead here
	void postCollisionUpdate(); //Clears up dead entities (Remove from list, clear pointers)

	std::vector<Entity*> getEntities();
};

