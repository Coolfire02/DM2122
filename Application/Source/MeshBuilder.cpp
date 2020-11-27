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
	std::vector<Vertex> vertex;
	Vertex v;

	v.pos.set(-100.0f, 0.0f, 0.0f); v.color.set(1.0f, 0.0f, 0.0f);  vertex.push_back(v);
	v.pos.set(100.0f, 0.0f, 0.0f); v.color.set(1.0f, 0.0f, 0.0f);  vertex.push_back(v);
	v.pos.set(0.0f, -100.0f, 0.0f); v.color.set(0.0f, 1.0f, 0.0f);  vertex.push_back(v);
	v.pos.set(0.0f, 100.0f, 0.0f); v.color.set(0.0f, 1.0f, 0.0f);  vertex.push_back(v);
	v.pos.set(0.0f, 0.0f, 100.0f); v.color.set(0.0f, 0.0f, 1.0f);  vertex.push_back(v);
	v.pos.set(0.0f, 0.0f, -100.0f); v.color.set(0.0f, 0.0f, 1.0f);  vertex.push_back(v);

	std::vector<GLuint> index_buffer_data;
	for (int i = 0; i < 6; i++) {
		index_buffer_data.push_back(i);
	}


	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_LINES;
	mesh->indexSize = index_buffer_data.size();

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

float coneX(float height, float totalHeight, int radius, int theta) {
	return height / totalHeight * radius * cos(Math::DegreeToRadian(theta));
}

float coneZ(float height, float totalHeight, int radius, int theta) {
	return height / totalHeight * radius * sin(Math::DegreeToRadian(theta));
}

Mesh* MeshBuilder::GenerateCone(const std::string& meshName, Color color)
{

	std::vector<Vertex> vertex;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.color = color;
	//for (theta = 0; theta <= 360; theta += 10) //slice
	//	add_vertex(RADIUS * x(theta), -HEIGHT / 2, RADIUS * z(theta))
	//	add_vertex(0, HEIGHT / 2, 0)
	//	for (theta = 0; theta <= 360; theta += 10) //bottom
	//		add_vertex(0, -HEIGHT / 2, 0)
	//		add_vertex(RADIUS * x(theta), -HEIGHT / 2, RADIUS * z(theta))

	for (int theta = 0; theta <= 360; theta += 10) {
		v.pos.set(1 * coneX())
	}

	
	

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_FAN;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}


static Mesh* GenerateTorus(const std::string& meshName, Color color) {
	std::vector<Vertex> vertex;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.color = color;

	
	int numStacks = 10;
	int numSlices = 200;
	int outerR = 10;
	int innerR = 5;
	float degreePerStack = 360.f / numStacks;
	float degreePerSlice = 360.f / numSlices;
	float x1, z1;
	float x2, y2, z2;
	for (unsigned int stack = 0; stack < numStacks + 1; stack++) {
		for (unsigned int slice = 0; slice < numSlices + 1; slice++) {
			z1 = outerR * cos(Math::DegreeToRadian(stack * degreePerStack));
			x1 = outerR * sin(Math::DegreeToRadian(stack * degreePerStack));
			z2 = (outerR + innerR * cos(Math::DegreeToRadian(slice * degreePerSlice)) * cos(Math::DegreeToRadian(stack * degreePerStack)));
			y2 = innerR * sin(Math::DegreeToRadian(slice * degreePerSlice));
			x2 = outerR + innerR * cos(Math::DegreeToRadian(slice * degreePerSlice)) * sin(Math::DegreeToRadian(stack * degreePerStack));
			v.pos.set(x2, y2, z2);
			v.normal.Set(x2 - x1, y2, z2 - z1);
			vertex.push_back(v);
		}
	}

	for (unsigned int stack = 0; stack < numStacks; stack++) {
		for (unsigned int slice = 0; slice < numSlices + 1; slice++) {
			index_buffer_data.push_back((numSlices + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlices + 1) * (stack + 1) + slice + 0);
		}

	}
}

float sphereX(int phi, int theta) {
	return cos(phi * Math::PI / 180) * cos(theta * Math::PI / 180);
}

float sphereY(int phi) {
	return sin(phi * Math::PI / 180);
}

float sphereZ(int phi, int theta) {
	return cos(phi * Math::PI / 180) * sin(theta * Math::PI / 180);
}

Mesh* MeshBuilder::GenerateSphere(const std::string& meshName, Color color, float radius) {
	
	double pi = atan(1) * 4;
	std::vector<Vertex> vertex;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.color = color;
	int index = 0;
	for (int phi = 0; phi < 180; phi += 10) {
		for (int theta = 0; theta <= 360; theta += 10) {
			
			v.normal.Set(sphereX(phi, theta), sphereY(phi) * (phi >= 90 ? -1 : 1), sphereZ(phi, theta));
			v.normal.Normalized();
			float x = 1 * sphereX(phi, theta);
			float y = 1 * sphereY(phi);
			if (phi >= 90)
				y *= -1;
			float z = 1 * sphereZ(phi, theta);
			v.pos.set(x, y, z);
			vertex.push_back(v);
			index_buffer_data.push_back(index++);

			x = 1 * cos((phi+10) * pi / 180 ) * cos(theta * pi / 180);
			y = 1 * sin((phi+10) * pi / 180);
			if (phi >= 90)
				y *= -1;
			z = 1 * cos((phi+10) * pi / 180) * sin(theta * pi / 180);

			v.pos.set(x, y, z);
			vertex.push_back(v);
			index_buffer_data.push_back(index++);
		}
	}
	/*for (int theta = 0; theta <= 360; theta += 10) {
		v.pos.set(0, 0, 0);
		vertex.push_back(v);
		index_buffer_data.push_back(index++);

		int x = radius * cos(theta * pi / 180);
		int z = radius * sin(theta * pi / 180);
		v.pos.set(x, 0, z);
		vertex.push_back(v);
		index_buffer_data.push_back(index++);
	}*/

	//for (int theta = 0; theta <= 360; theta += 10) {
	//	v.pos.set(0, 0, 0);
	//	vertex.push_back(v);

	//	int x = radius * cos(theta / 180 * pi);
	//	int z = radius * sin(theta / 180 * pi);
	//	v.pos.set(x, 1, z);
	//}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

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
	v.pos.set(0.5f, 0.5f, 0.5f); v.color.set(0.0f, 1.0f, 0.0f);  vertex.push_back(v);
	v.pos.set(-0.5f, 0.5f, 0.5f); v.color.set(0.0f, 1.0f, 0.0f); vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, 0.5f); v.color.set(0.0f, 1.0f, 0.0f); vertex.push_back(v);

	v.pos.set(0.5f, 0.5f, 0.5f); v.color.set(0.0f, 1.0f, 0.0f); vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, 0.5f); v.color.set(0.0f, 1.0f, 0.0f); vertex.push_back(v);
	v.pos.set(0.5f, -0.5f, 0.5f); v.color.set(0.0f, 1.0f, 0.0f); vertex.push_back(v);

	v.pos.set(-0.5f, 0.5f, 0.5f); v.color.set(1.0f, 0.0f, 0.0f); vertex.push_back(v); //forward left
	v.pos.set(-0.5f, 0.5f, -0.5f); v.color.set(1.0f, 0.0f, 0.0f); vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, -0.5f); v.color.set(1.0f, 0.0f, 0.0f); vertex.push_back(v);

	v.pos.set(-0.5f, 0.5f, 0.5f); v.color.set(1.0f, 0.0f, 0.0f); vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, -0.5f); v.color.set(1.0f, 0.0f, 0.0f); vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, 0.5f); v.color.set(1.0f, 0.0f, 0.0f); vertex.push_back(v);

	v.pos.set(-0.5f, 0.5f, -0.5f); v.color.set(0.0f, 0.0f, 1.0f);  vertex.push_back(v); //forward back
	v.pos.set(0.5f, -0.5f, -0.5f); v.color.set(0.0f, 0.0f, 1.0f); vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, -0.5f); v.color.set(0.0f, 0.0f, 1.0f); vertex.push_back(v);

	v.pos.set(-0.5f, 0.5f, -0.5f); v.color.set(0.0f, 0.0f, 1.0f); vertex.push_back(v);
	v.pos.set(0.5f, 0.5f, -0.5f); v.color.set(0.0f, 0.0f, 1.0f); vertex.push_back(v);
	v.pos.set(0.5f, -0.5f, -0.5f); v.color.set(0.0f, 0.0f, 1.0f); vertex.push_back(v);

	v.pos.set(0.5f, 0.5f, -0.5f); v.color.set(0.7f, 0.0f, 0.7f); vertex.push_back(v); //forward right
	v.pos.set(0.5f, 0.5f, 0.5f);  v.color.set(0.7f, 0.0f, 0.7f); vertex.push_back(v);
	v.pos.set(0.5f, -0.5f, 0.5f); v.color.set(0.7f, 0.0f, 0.7f); vertex.push_back(v);

	v.pos.set(0.5f, 0.5f, -0.5f); v.color.set(0.7f, 0.0f, 0.7f); vertex.push_back(v);
	v.pos.set(0.5f, -0.5f, 0.5f); v.color.set(0.7f, 0.0f, 0.7f); vertex.push_back(v);
	v.pos.set(0.5f, -0.5f, -0.5f); v.color.set(0.7f, 0.0f, 0.7f); vertex.push_back(v);

	v.pos.set(0.5f, 0.5f, 0.5f); v.color.set(0.0f, 0.7f, 0.7f);  vertex.push_back(v);//up
	v.pos.set(0.5f, 0.5f, -0.5f); v.color.set(0.0f, 0.7f, 0.7f); vertex.push_back(v);
	v.pos.set(-0.5f, 0.5f, 0.5f); v.color.set(0.0f, 0.7f, 0.7f); vertex.push_back(v);

	v.pos.set(0.5f, 0.5f, -0.5f); v.color.set(0.0f, 0.7f, 0.7f); vertex.push_back(v);
	v.pos.set(-0.5f, 0.5f, -0.5f); v.color.set(0.0f, 0.7f, 0.7f); vertex.push_back(v);
	v.pos.set(-0.5f, 0.5f, 0.5f); v.color.set(0.0f, 0.7f, 0.7f); vertex.push_back(v);

	v.pos.set(0.5f, -0.5f, 0.5f); v.color.set(0.7f, 0.7f, 0.0f);  vertex.push_back(v);//down
	v.pos.set(-0.5f, -0.5f, 0.5f); v.color.set(0.7f, 0.7f, 0.0f); vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, -0.5f); v.color.set(0.7f, 0.7f, 0.0f); vertex.push_back(v);

	v.pos.set(0.5f, -0.5f, 0.5f); v.color.set(0.7f, 0.7f, 0.0f); vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, -0.5f); v.color.set(0.7f, 0.7f, 0.0f); vertex.push_back(v);
	v.pos.set(0.5f, -0.5f, -0.5f); v.color.set(0.7f, 0.7f, 0.0f); vertex.push_back(v);

	//Normal
	for (auto& element : vertex) {
		v.normal.Set(v.pos.x, v.pos.y, v.pos.z);
	}
	
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

	std::vector<GLuint> index_buffer_data;
	for (int i = 0; i < 36; i++) {
		index_buffer_data.push_back(i);
	}


	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();


	return mesh;
}