#include "ModelLoader.h"
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <vector>

RawModel ModelLoader::loadModel(const std::string& fileName, Loader& loader) {
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Assimp Error: " << importer.GetErrorString() << std::endl;
        throw std::runtime_error("Failed to load model: " + fileName);
    }

    aiMesh* mesh = scene->mMeshes[0];

    std::vector<float> vertices;
    std::vector<float> textureCoords;
    std::vector<float> normals;
    std::vector<unsigned int> indices;

    if (mesh->HasPositions()) {
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            vertices.push_back(mesh->mVertices[i].x);
            vertices.push_back(mesh->mVertices[i].y);
            vertices.push_back(mesh->mVertices[i].z);
        }
    }
    else {
        throw std::runtime_error("Model has no vertex positions.");
    }

    if (mesh->HasTextureCoords(0)) {
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            textureCoords.push_back(mesh->mTextureCoords[0][i].x);
            textureCoords.push_back(mesh->mTextureCoords[0][i].y);
        }
    }
    else {
        std::cout << "Warning: Model has no texture coordinates." << std::endl;
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            textureCoords.push_back(0.0f); // Default texture coordinate
            textureCoords.push_back(0.0f);
        }
    }

    if (mesh->HasNormals()) {
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            normals.push_back(mesh->mNormals[i].x);
            normals.push_back(mesh->mNormals[i].y);
            normals.push_back(mesh->mNormals[i].z);
        }
    }
    else {
        std::cout << "Warning: Model has no normals." << std::endl;
    }

    if (mesh->HasFaces()) {
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }
    }
    else {
        throw std::runtime_error("Model has no indices.");
    }

    return loader.loadToVAO(vertices, textureCoords, normals, indices);
}