#include "ShaderProgram.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

ShaderProgram::ShaderProgram(const std::string& vertexFile, const std::string& fragmentFile) {
    vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
    fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);

    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
}

void ShaderProgram::linkProgram()
{
    glLinkProgram(programID);
    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        throw std::runtime_error("Shader program linking failed.");
    }
    glValidateProgram(programID);
}

void ShaderProgram::start() {
    glUseProgram(programID);
}

void ShaderProgram::stop() {
    glUseProgram(0);
}

void ShaderProgram::cleanUp() {
    stop();
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    glDeleteProgram(programID);
}

void ShaderProgram::bindAttribute(int attribute, const std::string& variableName) {
    glBindAttribLocation(programID, attribute, variableName.c_str());
}

int ShaderProgram::getUniformLocation(std::string uniformName)
{
    return glGetUniformLocation(programID, uniformName.c_str());
}

void ShaderProgram::loadFloat(int location, float value)
{
    glUniform1f(location, value);
}

void ShaderProgram::loadVector(int location, glm::vec3 vector)
{
    glUniform3fv(location, 1, &vector[0]);
}

void ShaderProgram::loadBoolean(int location, bool value)
{
    glUniform1i(location, (int)value);
}

void ShaderProgram::loadMatrix(int location, glm::mat4 matrix)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::bindAttributes()
{
}

unsigned int ShaderProgram::loadShader(const std::string& file, unsigned int type) {
    std::ifstream shaderFile(file);
    if (!shaderFile.is_open()) {
        throw std::runtime_error("Failed to open shader file: " + file);
    }

    std::stringstream shaderSource;
    shaderSource << shaderFile.rdbuf();
    shaderFile.close();
    std::string shaderCode = shaderSource.str();
    const char* shaderCodeCStr = shaderCode.c_str();

    unsigned int shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &shaderCodeCStr, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        throw std::runtime_error("Shader compilation failed.");
    }

    return shaderID;
}