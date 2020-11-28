#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateCone(const std::string &meshName, Color color);
	static Mesh* GenerateSphere(const std::string& meshName, Color color, float radius);
	static Mesh* GenerateCube(const std::string &meshName, Color color);

	static Mesh* GenerateTorus(const std::string& meshName, Color color, int innerR, int outterR);
};

#endif