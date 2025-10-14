/*
    Header for Shaders
*/
#pragma once

#include <string>
#include <vector>
#include <aixlog.hpp>

namespace LARE{
class Shader{
    private:
        std::string shader;
    public:
        Shader(std::string shader);

        Shader();

        std::string readShader();
};
}