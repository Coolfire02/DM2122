#include <iostream>
#include <fstream>
#include <map>

#include "LoadOBJ.h"

bool LoadOBJ(
	const char *file_path, 
	std::vector<Position> & out_vertices, 
	std::vector<TexCoord> & out_uvs, 
	std::vector<Vector3> & out_normals
)
{
	//Fill up code from OBJ lecture notes

	std::ifstream fileStream(file_path, std::ios::binary);
	if (!fileStream.is_open()) {
		std::cout << "Impossible to open " << file_path << ". Are you in the right directory? \n" << std::endl;
		return false;
	}
	std::vector<unsigned> vertexIndices, uvIndices, nIndices;
	std::vector<Position> temp_vertices; //Temporary vertices
	std::vector<TexCoord> temp_uvs; //Temporary texture coordinates
	std::vector<Vector3> temp_ns; //Temporary normals
	while (!fileStream.eof()) {
		char buf[256];
		fileStream.getline(buf, 256);
		if (strncmp("v ", buf, 2) == 0) { //2 char "v " hence 2 for max count
			Position vertex;
			sscanf_s((buf + 2), "%f%f%f", &vertex.x, &vertex.y, &vertex.z); //Ignores whitespace
			temp_vertices.push_back(vertex);

			
		}
		else if (strncmp("vt ", buf, 3) == 0) {
			TexCoord uv;
			sscanf_s((buf + 2), "%f%f", &uv.u, &uv.v); 
			temp_uvs.push_back(uv);
		}
		else if (strncmp("vn ", buf, 3) == 0) {
			Vector3 normal;
			sscanf_s((buf + 2), "%f%f%f", &normal.x, &normal.y, &normal.z);
			temp_ns.push_back(normal);
		}
		else if (strncmp("f ", buf, 2) == 0) {
			unsigned int vertexIndex[4], uvIndex[4], nIndex[4];
			int matches = sscanf_s((buf + 2), "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", 
				&vertexIndex[0], &uvIndex[0], &nIndex[0],
				&vertexIndex[1], &uvIndex[1], &nIndex[1],
				& vertexIndex[2], &uvIndex[2], &nIndex[2],
				& vertexIndex[3], &uvIndex[3], &nIndex[3]);
			switch (matches) {
			case 9:
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices	 .push_back(uvIndex[0]);
				uvIndices	 .push_back(uvIndex[1]);
				uvIndices	 .push_back(uvIndex[2]);
				nIndices	 .push_back(nIndex[0]);
				nIndices	 .push_back(nIndex[1]);
				nIndices	 .push_back(nIndex[2]);
				break;
			case 12:
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices	 .push_back(uvIndex[0]);
				uvIndices	 .push_back(uvIndex[1]);
				uvIndices	 .push_back(uvIndex[2]);
				nIndices	 .push_back(nIndex[0]);
				nIndices	 .push_back(nIndex[1]);
				nIndices	 .push_back(nIndex[2]);

				vertexIndices.push_back(vertexIndex[2]);
				vertexIndices.push_back(vertexIndex[3]);
				vertexIndices.push_back(vertexIndex[0]);
				uvIndices	 .push_back(uvIndex[2]);
				uvIndices	 .push_back(uvIndex[3]);
				uvIndices	 .push_back(uvIndex[0]);
				nIndices	 .push_back(nIndex[2]);
				nIndices	 .push_back(nIndex[3]);
				nIndices	 .push_back(nIndex[0]);

				break;
			default:
				std::cout << "Invalid Face Parsed." << std::endl;
			}
		}
	}
	fileStream.close();
	for (unsigned i = 0; i < vertexIndices.size(); ++i) {
		//Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int nIndex = nIndices[i];

		// Get the attributes thanks to the index -1 cause index starts at 1
		Position vertex = temp_vertices[vertexIndex - 1];
		TexCoord uv = temp_uvs[uvIndex - 1];
		Vector3 normal = temp_ns[nIndex - 1];

		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);
	}

	return true;
}

struct PackedVertex{
	Position position;
	TexCoord uv;
	Vector3 normal;
	bool operator<(const PackedVertex that) const{
		return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
	};
};

bool getSimilarVertexIndex_fast( 
	PackedVertex & packed, 
	std::map<PackedVertex, unsigned short> & VertexToOutIndex,
	unsigned short & result
){
	std::map<PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);
	if(it == VertexToOutIndex.end())
	{
		return false;
	}
	else
	{
		result = it->second;
		return true;
	}
}

void IndexVBO(
	std::vector<Position> & in_vertices,
	std::vector<TexCoord> & in_uvs,
	std::vector<Vector3> & in_normals,

	std::vector<unsigned> & out_indices,
	std::vector<Vertex> & out_vertices
)
{
	std::map<PackedVertex,unsigned short> VertexToOutIndex;

	// For each input vertex
	for(unsigned int i = 0; i < in_vertices.size(); ++i) 
	{

		PackedVertex packed = {in_vertices[i], in_uvs[i], in_normals[i]};

		// Try to find a similar vertex in out_XXXX
		unsigned short index;
		bool found = getSimilarVertexIndex_fast( packed, VertexToOutIndex, index);

		if ( found )
		{ 
			// A similar vertex is already in the VBO, use it instead !
			out_indices.push_back( index );
		}
		else
		{ 
			// If not, it needs to be added in the output data.
			Vertex v;
			v.pos.set(in_vertices[i].x, in_vertices[i].y, in_vertices[i].z);
			v.texCoord.Set(in_uvs[i].u, in_uvs[i].v);
			v.normal.Set(in_normals[i].x, in_normals[i].y, in_normals[i].z);
			v.color.set(1, 1, 1);
			out_vertices.push_back(v);
			unsigned newindex = (unsigned)out_vertices.size() - 1;
			out_indices.push_back( newindex );
			VertexToOutIndex[ packed ] = newindex;
		}
	}
}