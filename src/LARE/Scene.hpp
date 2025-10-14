/*
    A scene is a simple     
*/
#pragma once

#include <string>
#include <vector>

#include <Object.hpp>

namespace LARE{
    class Object;
    
    class Scene{
    private:
        std::string name;
    public:
        std::vector<Object*> objects;

        Scene(std::string sceneName);

        void addObject(Object* object){
            this->objects.push_back(object);
        }
    };
}