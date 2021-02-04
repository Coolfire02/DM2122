#pragma once
#include "Mesh.h"
#include "MatrixStack.h"

class SceneManager
{
	void RenderMesh(Mesh* mesh, bool lightEnabled);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
};

