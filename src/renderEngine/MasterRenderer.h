#pragma once
#include "EntityRenderer.h"
#include "shaders/StaticShader.h"
#include "models/TexturedModel.h"
#include "entities/Entity.h"
#include <map>
#include <vector>
#include <glm/glm.hpp>
#include <optional>
#include "TerrainRenderer.h"

class MasterRenderer {
public:
	MasterRenderer();
	void render(Light sun, Camera camera);
	void cleanUp();
	void prepare();
	void createProjectionMatrix();
	void processEntity(Entity entity);
	void processTerrain(Terrain terrain);
	static void enableCulling();
	static void disableCulling();

private:
	static const float FOV;
	static const float FAR_PLANE;
	static const float NEAR_PLANE;
	static const float RED;
	static const float GREEN;
	static const float BLUE;
	
	glm::mat4 projectionMatrix;
	StaticShader shader;
	TerrainShader terrainShader;

	std::optional<EntityRenderer> renderer;
	std::optional<TerrainRenderer> terrainRenderer;
	std::vector<Terrain> terrains;
	std::map <TexturedModel, std::vector<Entity>> entities;

	
	

};