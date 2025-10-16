/*
    LARE Main Engine header
*/
#pragma once
#include <Renderer.hpp>
#include <Scene.hpp>
#include <Scripting.hpp>

#include <aixlog.hpp>
#include <glm/glm.hpp>
#include <string>

namespace LARE{
    typedef struct{
        std::string windowTitle;
        int width, height, alias;
    } EngineOptions;

    class LARE{
    private:
        Renderer* renderer;
    public:
        LARE(EngineOptions options);

        int Tick(Scene* scene);

        Renderer* getRenderer(){
            return renderer;
        }

        ~LARE();
    };
}