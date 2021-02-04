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
		if (loc.getX >= botLeftPos->getX() && loc.getX <= topRightPos->getX() &&
			loc.getY >= botLeftPos->getY() && loc.getY <= topRightPos->getY() &&
			loc.getZ <= botLeftPos->getZ() && loc.getZ >= topRightPos->getZ()) //Right hand rule
			return true;
		return false;
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

	//bool hasMultipleBoxes;
	//std::vector<Box*> originalHitBoxes; Too Complex, not for Assignment 2
	
public:
	HitBox(Box* box);
	HitBox();
	//HitBox(std::vector<Box*> boxes);
	~HitBox();

	//void setHitBox(std::vector<Box*> boxes);

	//This should be the Box that is defined before any scaling (Size after gen'd from MeshBuilder).
	void setOriginalHitBox(Box* box);

	void update(Mtx44 matrix); //Updates the entire hitbox's location based of the current obj Location
	//Further optimizations can be done with update, making Hitbox not get recalculated every frame if Location & size both are
	//not updated. But lack of time atm so that'll have to come in the future.
};

