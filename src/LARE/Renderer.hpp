/*
    LARE Renderer
*/
#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <aixlog.hpp>
#include <string>

#include <Scene.hpp>
#include <Model.hpp>
#include <Object.hpp>
#include <Camera.hpp>
#include <Skybox.hpp>

namespace LARE{
    class LARE;

    typedef struct {
        float r,g,b,a;
    } ClearColor;

    class Renderer{
    private:
        int width, height;

        std::string windowTitle;

        GLFWwindow* window;

        ClearColor clearColor{0.0f, 0.0f, 0.0f, 255.0f};
        Skybox* skyBox;

        int checkShaderComp(unsigned int shader);

        Camera* cam;

        LARE* engine;
    public:
        Renderer(std::string wTitle, int w, int h, int alias, LARE* engine);

        int UpdateScene(Scene* scene);

        void GenerateShaders(Object* object);

        void GenerateObjectShader(Object* object);

        // Resize viewport
        void ResizeWindow();

        void setCamera(Camera* cam){
            this->cam = cam;
        }

        void setSkybox(Skybox* box){
            this->skyBox = box;
        }
    };

    static void setupWindowBuffer(GLFWwindow* win, int w, int h); 
}