/*
    File for skybox
*/
#pragma once

#include <Shader.hpp>

#include <vector>
#include <string>
#include <glad.h>
#include <aixlog.hpp>

namespace LARE
{
    class Skybox{
    private:
    public:
        unsigned int cubeMapTex, skyboxVAO, skyboxVBO, shaderID;

        Shader *vertexSkyboxShader, *fragSkyboxShader;
        /*
            [directory] should contain files that are named:
                right.jpg
                left.jpg
                top.jpg
                bottom.jpg
                front.jpg
                back.jpg
        */
        Skybox(std::string directory, std::string format = "jpg");
    };
} // LARE
