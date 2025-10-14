#include <Shader.hpp>

namespace LARE{
Shader::Shader(std::string shader) {
    this->shader = shader;
}

Shader::Shader(){
    // Do nothing, hope no one calls readShader
}

std::string Shader::readShader(){
    std::ifstream codeStream;
    codeStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try{
        codeStream.open(shader);
        std::stringstream shaderStream;
        shaderStream << codeStream.rdbuf();
        codeStream.close();
        return shaderStream.str();
    }catch(std::ifstream::failure e){
        LOG(ERROR, "LOG_ERROR") << "Failed to read shader file " << shader << "!\n";
        exit(-1);
        // Never reached
        return "NONE";
    }

    return "NONE";
}

} // LARE