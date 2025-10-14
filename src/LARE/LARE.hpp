/*
    LARE Main Engine header
*/
#pragma once
#include <Renderer.hpp>
#include <Scene.hpp>

#include <aixlog.hpp>
#include <glm/glm.hpp>
#include <string>

namespace LARE{
    typedef struct{
        std::string windowTitle;
        int width, height;
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