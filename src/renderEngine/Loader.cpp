#include "Loader.h"
#include <stb_image/stb_image.h>
#include <glad/glad.h>
#include <iostream>

RawModel Loader::loadToVAO(const std::vector<float>& positions, const std::vector<float>& textureCoords, const std::vector<float>& normals, const std::vector<unsigned int>& indices) {
    unsigned int vaoID = createVAO();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(0, 3, positions);
    storeDataInAttributeList(1, 2, textureCoords);
    storeDataInAttributeList(2, 3, normals);
    unbindVAO();
    return RawModel(vaoID, indices.size());
}

void Loader::cleanUp() {
    for (auto vao : vaos) {
        glDeleteVertexArrays(1, &vao);
    }
    for (auto vbo : vbos) {
        glDeleteBuffers(1, &vbo);
    }
}

unsigned int Loader::loadTexture(const std::string& fileName)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << fileName << std::endl;
        throw std::runtime_error("Failed to load texture");
    }

    GLenum format;
    if (nrChannels == 1) {
        format = GL_RED;
    }
    else if (nrChannels == 3) {
        format = GL_RGB;
    }
    else if (nrChannels == 4) {
        format = GL_RGBA;
    }
    else {
        stbi_image_free(data);
        throw std::runtime_error("Unsupported texture format");
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}

unsigned int Loader::createVAO() {
    unsigned int vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    vaos.push_back(vaoID);
    return vaoID;
}

void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, const std::vector<float>& data) {
    unsigned int vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(attributeNumber);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    vbos.push_back(vboID);
}

void Loader::unbindVAO() {
    glBindVertexArray(0);
}

void Loader::bindIndicesBuffer(const std::vector<unsigned int>& indices)
{
    unsigned int vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    vbos.push_back(vboID);
}
