/*
    Object in the 3D enviorment
*/
#pragma once

#include <Shader.hpp>
#include <Transform.hpp>

#include <string>

namespace LARE{
    class Model;
    class Script;

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

        Script* script;

        Object(std::string name);

        void initScript();

        void updateScript();

        void update();

        std::string getName(){
            return name;
        }
    };

}