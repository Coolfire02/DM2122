
#include "Mesh.h"
#include "GL\glew.h"

/******************************************************************************/
/*!
\brief
Default constructor - generate VBO/IBO here

\param meshName - name of mesh
*/
/******************************************************************************/
Mesh::Mesh(const std::string &meshName)
	: name(meshName)
	, mode(DRAW_TRIANGLES)
	, textureID(0)
{

	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &colorBuffer);
	glGenBuffers(1, &indexBuffer);
}

/******************************************************************************/
/*!
\brief
Destructor - delete VBO/IBO here
*/
/******************************************************************************/
Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &colorBuffer);
	glDeleteBuffers(1, &indexBuffer);
	if (textureID > 0)
		glDeleteTextures(1, &textureID);
}

/******************************************************************************/
/*!
\brief
OpenGL render code
*/
/******************************************************************************/
void Mesh::Render()
{
	glEnableVertexAttribArray(0); // 1st attribute buffer: vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer: color
	glEnableVertexAttribArray(2); // 3rd attribute buffer: normal
	if (textureID > 0)
		glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	//Vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//Colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));

	//Normal 
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));

	//Texture ID
	if (textureID > 0)
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));

	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	switch (mode) {
	case DRAW_LINES:
		glDrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, 0);
		break;
	case DRAW_TRIANGLE_STRIP:
		glDrawElements(GL_TRIANGLE_STRIP, indexSize, GL_UNSIGNED_INT, 0);
		break;
	case DRAW_TRIANGLES:
		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
		break;
	case DRAW_TRIANGLE_FAN:
		glDrawElements(GL_TRIANGLE_FAN, indexSize, GL_UNSIGNED_INT, 0);
		break;
	default:
		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
		break;
	}
	
	

	glDisableVertexAttribArray(0); //Vertices
	glDisableVertexAttribArray(1); //color
	glDisableVertexAttribArray(2); //normal
	if (textureID > 0)
		glDisableVertexAttribArray(3); //texture
}