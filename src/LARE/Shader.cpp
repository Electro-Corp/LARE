#include <Shader.hpp>
#include <Transform.hpp>

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

void Shader::setVec3(int id, const std::string &name, const glm::vec3 &value){
    glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z); 
}

void Shader::setVec4(int id, const std::string &name, const glm::vec4 &value){
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]); 
}

void Shader::setMat4(int id, const std::string &name, const glm::mat4 &value){
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}


} // LARE