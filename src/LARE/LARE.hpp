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
        ScriptManager* scriptManager;
    public:
        LARE(EngineOptions options);

        int Tick(Scene* scene);

        Renderer* getRenderer(){
            return renderer;
        }

        ScriptManager* getScriptMan(){
            return scriptManager;
        }

        // Key callback
        static void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods);


        ~LARE();
    };
}