#pragma once
#include <string>
#include <glm/glm.hpp>

class ShaderProgram {
public:
    ShaderProgram(const std::string& vertexFile, const std::string& fragmentFile);
    void linkProgram();
    void start();
    void stop();
    void cleanUp();

protected:
    void bindAttribute(int attribute, const std::string& variableName);
    int getUniformLocation(std::string uniformName);
    void loadFloat(int location, float value);
    void loadVector(int location, glm::vec3 vector);
    void loadBoolean(int location, bool value);
    void loadMatrix(int location, glm::mat4 matrix);
    virtual void bindAttributes() = 0;
    virtual void getAllUniformLocations() = 0;

private:
    unsigned int programID;
    unsigned int vertexShaderID;
    unsigned int fragmentShaderID;

    unsigned int loadShader(const std::string& file, unsigned int type);
};