#pragma once
#include "shaders/TerrainShader.h"
#include "terrains/Terrain.h"
#include <glm/glm.hpp>
#include <vector>

class TerrainRenderer {
private:
	TerrainShader shader;

	void prepareTerrain(Terrain terrain);
	void unbindTexturedModel();
	void loadModelMatrix(Terrain terrain);
public:
	TerrainRenderer(TerrainShader shader, glm::mat4 projectionMatrix);
	void render(std::vector<Terrain> terrains);
};