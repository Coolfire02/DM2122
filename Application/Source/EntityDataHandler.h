#pragma once

//struct EntityMeshData {
//	float
//		transX, transY, transZ,
//		rotMag, rotX, rotY, rotZ,
//		scaleX, scaleY, scaleZ;
//	EntityMeshData() : transX(0.f), transY(0.f), transZ(0.f),
//	rotMag(0.f), rotX(0.f), rotY(0.f), rotZ(0.f),
//	scaleX(0.f), scaleY(0.f), scaleZ(0.f) {}
//};

//Level 1, non hierarchical (First item in hierarchical stack will use the data from Entity's EntityData)
//This data is then used to communicate with the HitBox class to update it accordingly
struct EntityData {
	float
		transX, transY, transZ,
		rotMag, rotX, rotY, rotZ,
		scaleX, scaleY, scaleZ;
	EntityData() : transX(0.f), transY(0.f), transZ(0.f),
		rotMag(0.f), rotX(0.f), rotY(0.f), rotZ(0.f),
		scaleX(0.f), scaleY(0.f), scaleZ(0.f) {}
};
