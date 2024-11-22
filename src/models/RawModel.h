#pragma once

class RawModel {
public:
    RawModel(unsigned int vaoID, int vertexCount);
    RawModel();
    unsigned int getVaoID() const;
    int getVertexCount() const;

private:
    unsigned int vaoID;
    int vertexCount;
};