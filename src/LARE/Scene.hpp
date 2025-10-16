/*
    A scene is a simple     
*/
#pragma once

#include <string>
#include <vector>

#include <Object.hpp>
#include <Light.hpp>

namespace LARE{
    class Object;
    
    class Scene{
    private:
        std::string name;

    public:
        std::vector<Object*> objects;
        std::vector<Light*> lights;

        Scene(std::string sceneName);

        void addObject(Object* object){
            this->objects.push_back(object);
        }

        void findLights(){
            for(auto& obj : objects){
                if(obj->type == ObjectType::LIGHT){
                    this->lights.push_back((Light*)obj);
                }
            }
        }
    };
}