#pragma once
#include "models/RawModel.h"
#include "renderEngine/Loader.h"
#include "textures/ModelTexture.h"

class Terrain {
private:
	static const float SIZE;
	static const int VERTEX_COUNT;
	float x;
	float z;
	RawModel model;
	ModelTexture texture;

	RawModel generateTerrain(Loader& loader);

public:
	Terrain(int gridX, int gridZ, Loader loader, ModelTexture texture);
	RawModel getModel();
	ModelTexture getTexture();
	float getX();
	float getZ();
};