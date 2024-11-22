#include "Terrain.h"

const float Terrain::SIZE = 800.0f;
const int Terrain::VERTEX_COUNT = 128;

Terrain::Terrain(int gridX, int gridZ, Loader loader, ModelTexture texture) : texture(NULL)
{
	this->texture = texture;
	x = gridX * SIZE;
	z = gridZ * SIZE;
    model = generateTerrain(loader);
}

RawModel Terrain::getModel()
{
    return model;
}

ModelTexture Terrain::getTexture()
{
    return texture;
}

float Terrain::getX()
{
    return x;
}

float Terrain::getZ()
{
    return z;
}

RawModel Terrain::generateTerrain(Loader& loader)
{
    int count = VERTEX_COUNT * VERTEX_COUNT;

    std::vector<float> vertices(count * 3);
    std::vector<float> normals(count * 3);
    std::vector<float> textureCoords(count * 2);
    std::vector<unsigned int> indices(6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1));

    int vertexPointer = 0;
    for (int i = 0; i < VERTEX_COUNT; i++) {
        for (int j = 0; j < VERTEX_COUNT; j++) {
            vertices[vertexPointer * 3] = static_cast<float>(j) / (VERTEX_COUNT - 1) * SIZE;
            vertices[vertexPointer * 3 + 1] = 0.0f;
            vertices[vertexPointer * 3 + 2] = static_cast<float>(i) / (VERTEX_COUNT - 1) * SIZE;

            normals[vertexPointer * 3] = 0.0f;
            normals[vertexPointer * 3 + 1] = 1.0f;
            normals[vertexPointer * 3 + 2] = 0.0f;

            textureCoords[vertexPointer * 2] = static_cast<float>(j) / (VERTEX_COUNT - 1);
            textureCoords[vertexPointer * 2 + 1] = static_cast<float>(i) / (VERTEX_COUNT - 1);

            vertexPointer++;
        }
    }

    int pointer = 0;
    for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
        for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
            int topLeft = (gz * VERTEX_COUNT) + gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
            int bottomRight = bottomLeft + 1;

            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }
    }

    return loader.loadToVAO(vertices, textureCoords, normals, indices);
}
