#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	const GLfloat vertex_buffer_data[] = {
		0
	};
	const GLfloat color_buffer_data[] = {
		0
	};
	const GLuint index_buffer_data[] = {
		0
	};
	Mesh *mesh = new Mesh(meshName);

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, float lengthX, float lengthY)
{
	const GLfloat vertex_buffer_data[] = {
		0
	};
	const GLfloat color_buffer_data[] = {
		0
	};
	const GLuint index_buffer_data[] = {
		0
	};
	Mesh *mesh = new Mesh(meshName);

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	// Cube
	int index = 0;
	std::vector<Vertex> vertex;
	Vertex v;
	v.pos.set(0.5f, 0.5f, 0.5f); v.color.set(1.0f, 1.0f, 1.0f);  vertex.push_back(v);
	v.pos.set(-0.5f, 0.5f, 0.5f); vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, 0.5f); vertex.push_back(v);

	v.pos.set(0.5f, 0.5f, 0.5f); vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, 0.5f); vertex.push_back(v);
	v.pos.set(0.5f, -0.5f, 0.5f); vertex.push_back(v);

	v.pos.set(-0.5f, 0.5f, 0.5f); vertex.push_back(v); //forward left
	v.pos.set(-0.5f, 0.5f, -0.5f); vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, -0.5f); vertex.push_back(v);

	v.pos.set(-0.5f, 0.5f, 0.5f); vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, -0.5f); vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, 0.5f);  vertex.push_back(v);

	v.pos.set(-0.5f, 0.5f, -0.5f);   vertex.push_back(v); //forward back
	v.pos.set(0.5f, -0.5f, -0.5f);  vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, -0.5f);  vertex.push_back(v);

	v.pos.set(-0.5f, 0.5f, -0.5f);  vertex.push_back(v);
	v.pos.set(0.5f, 0.5f, -0.5f);  vertex.push_back(v);
	v.pos.set(0.5f, -0.5f, -0.5f); vertex.push_back(v);

	v.pos.set(0.5f, 0.5f, -0.5f); vertex.push_back(v); //forward right
	v.pos.set(0.5f, 0.5f, 0.5f);  vertex.push_back(v);
	v.pos.set(0.5f, -0.5f, 0.5f);  vertex.push_back(v);

	v.pos.set(0.5f, 0.5f, -0.5f);  vertex.push_back(v);
	v.pos.set(0.5f, -0.5f, 0.5f);  vertex.push_back(v);
	v.pos.set(0.5f, -0.5f, -0.5f);  vertex.push_back(v);

	v.pos.set(0.5f, 0.5f, 0.5f);   vertex.push_back(v);//up
	v.pos.set(0.5f, 0.5f, -0.5f);  vertex.push_back(v);
	v.pos.set(-0.5f, 0.5f, 0.5f);  vertex.push_back(v);

	v.pos.set(0.5f, 0.5f, -0.5f);  vertex.push_back(v);
	v.pos.set(-0.5f, 0.5f, -0.5f);  vertex.push_back(v);
	v.pos.set(-0.5f, 0.5f, 0.5f);  vertex.push_back(v);

	v.pos.set(0.5f, -0.5f, 0.5f);   vertex.push_back(v);//down
	v.pos.set(-0.5f, -0.5f, 0.5f);  vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, -0.5f);  vertex.push_back(v);

	v.pos.set(0.5f, -0.5f, 0.5f);  vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, -0.5f);  vertex.push_back(v);
	v.pos.set(0.5f, -0.5f, -0.5f);  vertex.push_back(v);


	
	const GLfloat color_buffer_data[] = {
		1.0f, 1.0f, 1.0f, //front
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,

		1.0f, 0.5f, 0.5f, //forward left
		1.0f, 0.5f, 0.5f,
		1.0f, 0.5f, 0.5f,

		1.0f, 0.5f, 0.5f,
		1.0f, 0.5f, 0.5f,
		1.0f, 0.5f, 0.5f,

		0.5f, 0.5f, 1.0f, //forward back
		0.5f, 0.5f, 1.0f,
		0.5f, 0.5f, 1.0f,

		0.5f, 0.5f, 1.0f, 
		0.5f, 0.5f, 1.0f,
		0.5f, 0.5f, 1.0f,

		0.5f, 1.0f, 1.0f, //forward right
		0.5f, 1.0f, 1.0f,
		0.5f, 1.0f, 1.0f,

		0.5f, 1.0f, 1.0f, 
		0.5f, 1.0f, 1.0f,
		0.5f, 1.0f, 1.0f,

		1.0f, 1.0f, 0.5f, //up
		1.0f, 1.0f, 0.5f,
		1.0f, 1.0f, 0.5f,

		1.0f, 1.0f, 0.5f,
		1.0f, 1.0f, 0.5f,
		1.0f, 1.0f, 0.5f,

	};

	const GLuint index_buffer_data[] = {
		0,1,2,
		3,4,5,
		6,7,8,
		9,10,11,
		12,13,14,
		15,16,17,
		18,19,20,
		21,22,23,
		24,25,26,
		27,28,29,
		30,31,32,
		33,34,35,
	};

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = 36;


	return mesh;
}