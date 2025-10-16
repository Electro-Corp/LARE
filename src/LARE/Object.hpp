/*
    Object in the 3D enviorment
*/
#pragma once

#include <Shader.hpp>
#include <Transform.hpp>

#include <string>

namespace LARE{
    class Model;

    enum ObjectType {
        MESH,
        LIGHT
    };

    class Object{
    private:
        std::string name;
    public:
        Shader fragmentShader, vertexShader;
        // OpenGL Shader Program
        unsigned int shaderProgram;
        
        // Object Type
        ObjectType type;

        Transform transform;
        
        Model* model;

        Object(std::string name);

        std::string getName(){
            return name;
        }
    };

}