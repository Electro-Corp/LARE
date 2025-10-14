/*
    A model holds multiple meshes
*/
#pragma once

#include <Mesh.hpp>
#include <Object.hpp>

#include <aixlog.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace LARE{
    class Model{
    private:
        Object* gm;

        std::vector<Mesh> meshes;
        std::string directory;

        // Optimize, don't load a texture
        // if we already did
        std::vector<Texture> loadedTexes;

        void loadModel(std::string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadMatTexes(aiMaterial* mat, aiTextureType type, std::string typeName);

    public:
        Model(Object* gm, char* path);

        void initMeshes();

        void drawModel(Camera* cam);
    };

    int genTexFromFile(const char* path, const std::string dir, bool gamma);
}