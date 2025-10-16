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

namespace LARE{
    typedef struct {
        float r,g,b,a;
    } ClearColor;

    class Renderer{
    private:
        int width, height;

        std::string windowTitle;

        GLFWwindow* window;

        ClearColor clearColor{0.0f, 0.0f, 0.0f, 255.0f};

        int checkShaderComp(unsigned int shader);

        Camera* cam;
    public:
        Renderer(std::string wTitle, int w, int h, int alias);

        int UpdateScene(Scene* scene);

        void GenerateShaders(Object* object);

        // Resize viewport
        void ResizeWindow();

        void setCamera(Camera* cam){
            this->cam = cam;
        }
    };

    static void setupWindowBuffer(GLFWwindow* win, int w, int h); 
}