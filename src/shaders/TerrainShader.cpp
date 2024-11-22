#include "TerrainShader.h"

TerrainShader::TerrainShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE),
location_transformationMatrix(NULL), location_projectionMatrix(NULL),
location_viewMatrix(NULL), location_lightPosition(NULL),
location_lightColor(NULL), location_shineDamper(NULL),
location_reflectivity(NULL), location_skyColor(NULL) {
    bindAttributes();
    linkProgram();
    getAllUniformLocations();
}

void TerrainShader::loadViewMatrix(Camera camera)
{
    glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
    loadMatrix(location_viewMatrix, viewMatrix);
}

void TerrainShader::loadTransformationMatrix(glm::mat4 transform)
{
    loadMatrix(location_transformationMatrix, transform);
}

void TerrainShader::loadProjectionMatrix(glm::mat4 projection) {
    loadMatrix(location_projectionMatrix, projection);
}

void TerrainShader::loadLight(Light light)
{
    loadVector(location_lightPosition, light.getPosition());
    loadVector(location_lightColor, light.getColor());
}

void TerrainShader::loadShineVariables(float damper, float reflectivity)
{
    loadFloat(location_shineDamper, damper);
    loadFloat(location_reflectivity, reflectivity);
}

void TerrainShader::loadSkyColor(float r, float g, float b)
{
    loadVector(location_skyColor, glm::vec3(r, g, b));
}

void TerrainShader::bindAttributes() {
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoordinates");
    bindAttribute(2, "normal");
}

void TerrainShader::getAllUniformLocations()
{
    location_transformationMatrix = getUniformLocation("transformationMatrix");
    location_projectionMatrix = getUniformLocation("projectionMatrix");
    location_viewMatrix = getUniformLocation("viewMatrix");
    location_lightPosition = getUniformLocation("lightPosition");
    location_lightColor = getUniformLocation("lightColor");
    location_shineDamper = getUniformLocation("shineDamper");
    location_reflectivity = getUniformLocation("reflectivity");
    location_skyColor = getUniformLocation("skyColor");
}