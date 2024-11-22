#pragma once

#include "models/RawModel.h"
#include <vector>
#include <string>

class Loader {
public:
    RawModel loadToVAO(const std::vector<float>& positions, const std::vector<float>& textureCoords, const std::vector<float>& normals, const std::vector<unsigned int>& indices);
    void cleanUp();
    unsigned int loadTexture(const std::string& fileName);

private:
    std::vector<unsigned int> vaos;
    std::vector<unsigned int> vbos;

    unsigned int createVAO();
    void storeDataInAttributeList(int attributeNumber, int coordinateSize, const std::vector<float>& data);
    void unbindVAO();
    void bindIndicesBuffer(const std::vector<unsigned int>& indices);
};