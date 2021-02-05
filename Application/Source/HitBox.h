#pragma once
#include "Position3D.h"
#include "EntityDataHandler.h"
#include "Mtx44.h"
#include <vector>

struct Box {
	Position3D* botLeftPos;
	Position3D* topRightPos;
	
	Box(Position3D* botLeft, Position3D* topRight) : botLeftPos(botLeft), topRightPos(topRight) {}

	bool locIsInBox(Position3D loc) {
		if (loc.getX() >= botLeftPos->getX() && loc.getX() <= topRightPos->getX() &&
			loc.getY() >= botLeftPos->getY() && loc.getY() <= topRightPos->getY() &&
			loc.getZ() <= botLeftPos->getZ() && loc.getZ() >= topRightPos->getZ()) //Right hand rule
			return true;
		return false;
	}

	bool locIsInBox(Box* box) {
		std::vector<Position3D*> pos;
		Position3D* botLeftFront = box->botLeftPos; pos.push_back(botLeftFront);
		Position3D* topRightBack = box->topRightPos; pos.push_back(topRightPos);

		Position3D botRightFront = Position3D(topRightBack->getX(), botLeftFront->getY(), botLeftFront->getZ()); pos.push_back(&botRightFront);
		Position3D topLeftBack = Position3D(botLeftFront->getX(), topRightBack->getY(), topRightBack->getZ()); pos.push_back(&topLeftBack);

		Position3D botLeftBack = Position3D(botLeftFront->getX(), botLeftFront->getY(), topLeftBack.getZ()); pos.push_back(&botLeftBack);
		Position3D botRightBack = Position3D(botRightFront.getX(), botRightFront.getY(), topRightBack->getZ()); pos.push_back(&botRightBack);

		Position3D topRightFront = Position3D(topRightBack->getX(), topRightBack->getY(), botLeftFront->getZ()); pos.push_back(&topRightFront);
		Position3D topLeftFront = Position3D(topLeftBack.getX(), topLeftBack.getY(), botLeftFront->getZ()); pos.push_back(&topLeftFront);

		for (auto& entry : pos) {
			if (!locIsInBox(*entry))
				return false;
		}
		return true;
	}
	~Box() {
		delete botLeftPos;
		delete topRightPos;
	}
};

/**
* Assume that all HitBoxes are "Boxes", found at the origin of an object, these Boxes can only be scaled,
* and cannot be associated with Hierarchical Models (Aka no HitBox for each mesh, but a general rectangle) for entire Entity.
* Issues with this are: L shaped objects will have to sacrifice either the horizontal or vertical collision as
* this HitBox only supports One. Single. Square. Box. Per. Entity. If you wish to work on this further for SP go ahead
* but I'm dying rn trying to come up with a proper collision system (How to interact with an Mtx44 (Based of projection/model stack or wtever) & Mesh BotLeft & Top Right Cords to come up with Hitbox?)
* plus I don't have time, 5 days till submission, whatever complex system I couldn't learn in this 5 days. So oh well
*/
class HitBox
{
	Box* originalBox;
	float size;

	Box* thisTickBox;

	//bool hasMultipleBoxes;
	//std::vector<Box*> originalHitBoxes; Too Complex, not for Assignment 2
	
public:
	HitBox(Box* box);
	HitBox();
	//HitBox(std::vector<Box*> boxes);
	~HitBox();

	Box* getOriginalBox();
	Box* getThisTickBox();

	//void setHitBox(std::vector<Box*> boxes);

	//This should be the Box that is defined before any scaling (Size after gen'd from MeshBuilder).
	void setOriginalHitBox(Box* box);

	void update(Mtx44 matrix); //Updates the entire hitbox's location based of the current obj Location
	//Further optimizations can be done with update, making Hitbox not get recalculated every frame if Location & size both are
	//not updated. But lack of time atm so that'll have to come in the future.

	bool collidedWith(HitBox other);
};

