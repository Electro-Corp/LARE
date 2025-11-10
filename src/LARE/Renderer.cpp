#include <Renderer.hpp>

namespace LARE{

Renderer::Renderer(std::string wTitle, int w, int h, int alias){
    this->windowTitle = wTitle;
    this->width = w;
    this->height = h;

    LOG(INFO, "LOG_INFO") << "Creating window (" << w << ", " << h << ")\n";

    // Init glfw
    glfwInit();
    // Set OpenGL params
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, alias);
    // Create window
    window = glfwCreateWindow(width, height, wTitle.c_str(), nullptr, nullptr);
    // Yeah?
    if(!window){
        // no...
        LOG(ERROR, "LOG_ERROR") << "Failed to create window!\n";
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    // Set user pointer
	glfwSetWindowUserPointer(window, this);
    // Init GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        LOG(ERROR, "LOG_ERROR") << "Failed to initilize GLAD!\n";
        exit(-1);
    }

    // init viewport
    glViewport(0, 0, width, height);
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    // Enable MSAA
    glEnable(GL_MULTISAMPLE);
    // Enable SRGB Gamma correction
    glEnable(GL_FRAMEBUFFER_SRGB);
    // Enable culling
    glEnable(GL_CULL_FACE);
    // Enable stencil testing 
    glEnable(GL_STENCIL_TEST);

    // Setup resize
    glfwSetFramebufferSizeCallback(window, setupWindowBuffer);  
}

int Renderer::UpdateScene(Scene* scene){
    if(glfwWindowShouldClose(window)){
        return -1;
    }
    // Clear color
    glClearColor(clearColor.r / 255.0f, clearColor.g / 255.0f, clearColor.b / 255.0f, clearColor.a / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    cam->camData.proj = glm::perspective(glm::radians((float)cam->pAngle), (float)width / (float)height, 0.1f, 100.0f);

    // Render each object
	for (auto& gm : scene->objects) {
        // Does it actually have something to render
        if(gm->model){
            // Set light data
            if(gm->type != ObjectType::LIGHT){
                int id = gm->shaderProgram;
                glUseProgram(id);

                Shader::setVec3(id, "viewPosition", Transform::internalToGLM(cam->position));

                Shader::setVec3(id, "light.ambient", Transform::internalToGLM(scene->lights[0]->color));
                Shader::setVec3(id, "light.specular", Transform::internalToGLM(scene->lights[0]->specular));
                Shader::setVec3(id, "light.diffuse", Transform::internalToGLM(scene->lights[0]->diffuse));
                Shader::setVec3(id, "light.position", scene->lights[0]->transform.getPosition());
            }
            if(skyBox != nullptr){
                glBindTexture(GL_TEXTURE_CUBE_MAP, skyBox->cubeMapTex);
            }
		    gm->model->drawModel(cam);
        }
	}
    
    // Shadow volume (Carmack's Reverse)
    // Disable writing to color buffer
    /*glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    // Disable depth buffer
    glDepthMask(GL_FALSE);

    glCullFace(GL_FRONT);
    glStencilOp(GL_INCR, GL_ZERO, GL_ZERO);
    glStencilFunc(GL_EQUAL, 1, 0xFF);

    glCullFace(GL_BACK);

    // Re-enable color buffer
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    // Re-enable depth buffer
    glDepthMask(GL_TRUE);*/

    // Draw our skybox (if we got one)
    if(skyBox != nullptr){
        glDepthFunc(GL_LEQUAL);
        glUseProgram(skyBox->shaderID);  
        Shader::setMat4(skyBox->shaderID, "view", glm::mat4(glm::mat3(cam->camData.view)));  
        Shader::setMat4(skyBox->shaderID, "proj", cam->camData.proj);
        // Render the cube
        glBindVertexArray(skyBox->skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyBox->cubeMapTex);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();

    return 0;
}

void Renderer::GenerateShaders(Object* object){
    // Compile vertex shader
    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vTemp = object->vertexShader.readShader();
    const char* vertexCode = vTemp.c_str();
    glShaderSource(vShader, 1, &vertexCode, NULL);
    glCompileShader(vShader);
    // Did it compile correctly...
    if(checkShaderComp(vShader)){
        LOG(INFO, "LOG_INFO") << "Vertex shader on " << object->getName() << " compiled.\n";
    }
    // Compile fragment shader
    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fTemp = object->fragmentShader.readShader();
    const char* fragmentCode = fTemp.c_str();
    glShaderSource(fShader, 1, &fragmentCode, NULL);
    glCompileShader(fShader);
    // Did it compile correctly...
    if(checkShaderComp(fShader)){
        LOG(INFO, "LOG_INFO") << "Fragment shader on " << object->getName() << " compiled.\n";
    }
    // Shader program !
    unsigned int sProgram = glCreateProgram();
    glAttachShader(sProgram, vShader);
    glAttachShader(sProgram, fShader);
    glLinkProgram(sProgram);
    // Did it error out...
    int suc;
    char log[512];
    glGetProgramiv(sProgram, GL_LINK_STATUS, &suc);
    if (!suc) {
        glGetProgramInfoLog(sProgram, sizeof(log), NULL, log);
        LOG(ERROR, "LOG_ERROR") << "OpenGL: Error linking shader program, log: " <<  std::string{log};
    }
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    
    object->shaderProgram = sProgram;

    LOG(INFO, "LOG_INFO") << "Shader program for " << object->getName() << " created.\n";

    if(object->model)
        object->model->initMeshes();
}

int Renderer::checkShaderComp(unsigned int shader) {
	int suc;
	char log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &suc);
	if (!suc) {
		glGetShaderInfoLog(shader, sizeof(log), NULL, log);
		LOG(ERROR, "LOG_ERROR") << "OpenGL: Error compiling shader, log:\n" << std::string{log};
	}
    return suc;
}

void Renderer::ResizeWindow(){
    glfwGetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);
}


static void setupWindowBuffer(GLFWwindow* win, int w, int h) {
	auto renderer = reinterpret_cast<Renderer*>(glfwGetWindowUserPointer(win));
	renderer->ResizeWindow();
}

} // LARE
