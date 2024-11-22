#include "RawModel.h"

RawModel::RawModel(unsigned int vaoID, int vertexCount) : vaoID(vaoID), vertexCount(vertexCount) {}

RawModel::RawModel() : vaoID(0), vertexCount(0){}

unsigned int RawModel::getVaoID() const {
    return vaoID;
}

int RawModel::getVertexCount() const {
    return vertexCount;
}