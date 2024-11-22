#pragma once
#include "models/RawModel.h"
#include "models/TexturedModel.h"
#include "shaders/StaticShader.h"
#include "entities/Entity.h"
#include <glm/glm.hpp>
#include <map>
#include <vector>

class EntityRenderer {
public:
    EntityRenderer(StaticShader shader, glm::mat4 projectionMatrix);
    void render(std::map<TexturedModel, std::vector<Entity>> entities);
private:
    StaticShader shader;

    void prepareTexturedModel(TexturedModel model);
    void unbindTexturedModel();
    void prepareInstance(Entity entity);
};