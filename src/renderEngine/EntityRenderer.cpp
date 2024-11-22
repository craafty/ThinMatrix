#include "EntityRenderer.h"
#include "DisplayManager.h"
#include "MasterRenderer.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "toolbox/Maths.h"
#include "models/TexturedModel.h"

EntityRenderer::EntityRenderer(StaticShader shader, glm::mat4 projectionMatrix) : shader(shader)
{
    shader.start();
    shader.loadProjectionMatrix(projectionMatrix);
    shader.stop();
}

void EntityRenderer::render(std::map<TexturedModel, std::vector<Entity>> entities)
{
    for (auto& pair : entities) {
        TexturedModel model = pair.first;
        std::vector<Entity>& entityList = pair.second; 

        prepareTexturedModel(model);

        for (const Entity& entity : entityList) {
            prepareInstance(entity);
            glDrawElements(GL_TRIANGLES, model.getRawModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);
        }

        unbindTexturedModel();
    }
}

void EntityRenderer::prepareTexturedModel(TexturedModel model)
{
    RawModel rawModel = model.getRawModel();
    glBindVertexArray(rawModel.getVaoID());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    ModelTexture texture = model.getTexture();
    if (texture.isHasTransparency()) {
        MasterRenderer::disableCulling();
    }
    shader.loadFakeLightingVariable(texture.isUseFakeLighting());
    shader.loadShineVariables(texture.getShineDamper(), texture.getReflectivity());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());
}

void EntityRenderer::unbindTexturedModel()
{
    MasterRenderer::enableCulling();
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void EntityRenderer::prepareInstance(Entity entity)
{
    glm::mat4 transformationMatrix = Maths::createTransformationMatrix(
        entity.getPosition(), entity.getRotX(), entity.getRotY(), entity.getRotZ(), entity.getScale());
    shader.loadTransformationMatrix(transformationMatrix);
}
