#pragma once
#include <string>
#include "models/RawModel.h"
#include "Loader.h"

class ModelLoader {
public:
	static RawModel loadModel(const std::string& fileName, Loader& loader);
};