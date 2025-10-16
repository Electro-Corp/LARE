#include <Model.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace LARE{

Model::Model(Object* gm, char* path){
    this->gm = gm;

    stbi_set_flip_vertically_on_load(true);

    this->loadModel(path);
}

void Model::loadModel(std::string path){
    LOG(INFO, "LOG_INFO") << "Model: Loading " << path << "\n";

    // Use assimp to load
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        LOG(ERROR, "LOG_ERROR") << "Model: Failed to load model " << path << "\nError: " << import.GetErrorString() << "\n";
        exit(-1);
    }

    directory = path.substr(0, path.find_last_of("/"));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene){
    // process node meshes
    for(int i = 0; i < node->mNumMeshes; i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // time for the mesh children
    for(int i = 0; i < node->mNumChildren; i++){
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene){
    // What things we need
    std::vector<Vertex> verts;
    std::vector<uint16_t> inds;
    std::vector<Texture> texes;

    // go through each vert..
    for(int i = 0; i < mesh->mNumVertices; i++){
        Vertex vert;

        glm::vec3 vec;
        vec.x = mesh->mVertices[i].x;
        vec.y = mesh->mVertices[i].y;
        vec.z = mesh->mVertices[i].z;
        vert.pos = vec;

        if(!mesh->mNormals){
            vec.x = 0;
            vec.y = 0;
            vec.z = 0;
            vert.normal = vec;
        }else{
            vec.x = mesh->mNormals[i].x;
            vec.y = mesh->mNormals[i].y;
            vec.z = mesh->mNormals[i].z;
            vert.normal = vec;
        }

        if(mesh->mTextureCoords[0]){
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vert.texCoord = vec;
        }else{
            LOG(WARNING, "LOG_WARN") << "Model: Mesh doesn't have texture coords!";
            vert.texCoord = glm::vec2(0.0f, 0.0f);
        }
        verts.push_back(vert);
    }

    for(int i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for(int j = 0; j < face.mNumIndices; j++){
            inds.push_back(face.mIndices[j]);
        }
    }

    if(mesh->mMaterialIndex >= 0){
        aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffMaps = loadMatTexes(mat, aiTextureType_DIFFUSE, "texture_diffuse");
        texes.insert(texes.end(), diffMaps.begin(), diffMaps.end());

        std::vector<Texture> specMaps = loadMatTexes(mat, aiTextureType_SPECULAR, "texture_specular");
        texes.insert(texes.end(), specMaps.begin(), specMaps.end());

        std::vector<Texture> normalMaps = loadMatTexes(mat, aiTextureType_NORMALS, "texture_normal");
        texes.insert(texes.end(), normalMaps.begin(), normalMaps.end());
    }

    return Mesh(verts, inds, texes);
}

std::vector<Texture> Model::loadMatTexes(aiMaterial* mat, aiTextureType type, std::string typeName){
    std::vector<Texture> texes;
    for(int i = 0; i < mat->GetTextureCount(type); i++){
        aiString str;
        mat->GetTexture(type, i, &str);
        bool s = false;
        for(int j = 0; j < loadedTexes.size(); j++){
            if(std::strcmp(loadedTexes[j].path.data(), str.C_Str()) == 0){
                texes.push_back(loadedTexes[j]);
                s = true;
            }
        }
        if(!s){
            Texture tex;
            tex.id = genTexFromFile(str.C_Str(), directory, 0.0);
            tex.type = typeName;
            tex.path = str.C_Str();
            loadedTexes.push_back(tex);
            texes.push_back(tex);
        }
    }
    return texes;
}

void Model::initMeshes(){
    for(auto& mesh : meshes){
        mesh.initMesh();
    }
}


void Model::drawModel(Camera* cam){
    for(int i = 0; i < meshes.size(); i++){
        meshes[i].drawMesh(gm->shaderProgram, gm->transform, cam);
    }
}


// Generate GL texture from file 
int genTexFromFile(const char* path, const std::string dir, bool gamma){
    std::string fName = path;
    std::replace(fName.begin(), fName.end(), '\\', '/');
    fName = dir + "/" + fName;

    LOG(INFO, "LOG_INFO") << "Model: Loading texture " << fName << "\n";

    unsigned int texId;
    glGenTextures(1, &texId);

    int w, h, n;
    unsigned char* data = stbi_load(fName.c_str(), &w, &h, &n, 0);
    if(data){
        GLenum format;
        switch(n){
            case 1:
                format = GL_RED;
                break;
            case 3:
                format = GL_RGB;
                break;
            case 4:
                format = GL_RGBA;
                break;
        }

        glBindTexture(GL_TEXTURE_2D, texId);
        glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }else{
        // TODO: In the future load a missing texture file
        LOG(ERROR, "LOG_ERROR") << "Model: Failed to generate texture " << path << "\n";
        stbi_image_free(data);
        return -1;
        //exit(-1);
    }

    return texId;
}

} // LARE;