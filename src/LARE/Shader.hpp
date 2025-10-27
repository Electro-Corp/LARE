/*
    Header for Shaders
*/
#pragma once

#include <string>
#include <vector>
#include <aixlog.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>


namespace LARE{
class Shader{
    private:
        std::string shader;
    public:
        
        Shader(std::string shader);

        Shader();

        std::string readShader();

        // Modify shader stuff
        static void setVec3(int id, const std::string &name, const glm::vec3 &value);

        static void setVec4(int id, const std::string &name, const glm::vec4 &value);

        static void setMat4(int id, const std::string &name, const glm::mat4 &value);
};
}