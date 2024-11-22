#pragma once
#include "ShaderProgram.h"
#include "entities/Camera.h"
#include "toolbox/Maths.h"
#include "entities/light.h"
#include <string>

class StaticShader : public ShaderProgram {
public:
    StaticShader();
    void loadViewMatrix(Camera camera);
    void loadTransformationMatrix(glm::mat4 matrix);
    void loadProjectionMatrix(glm::mat4 projection);
    void loadLight(Light light);
    void loadShineVariables(float damper, float reflectivity);
    void loadFakeLightingVariable(bool useFake);
    void loadSkyColor(float r, float g, float b);

protected:
    void bindAttributes() override;
    void getAllUniformLocations() override;

private:
    static constexpr const char* VERTEX_FILE = SOURCE_PATH "shaders/vertexShader.glsl";
    static constexpr const char* FRAGMENT_FILE = SOURCE_PATH "shaders/fragmentShader.glsl";
    int location_transformationMatrix;
    int location_projectionMatrix;
    int location_viewMatrix;
    int location_lightPosition;
    int location_lightColor;
    int location_shineDamper;
    int location_reflectivity;
    int location_useFakeLighting;
    int location_skyColor;
};