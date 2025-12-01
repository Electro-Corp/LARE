#include <LARE.hpp>

namespace LARE{
// LARE
LARE* currentLareInstance;

LARE::LARE(EngineOptions options){
    currentLareInstance = this;
    // Init logging
    AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace);
    LOG(INFO, "LOG_INFO") << "LARE Starting... (compiled on " << __DATE__ << " @ " << __TIME__ << ")\n";
    LOG(INFO, "LOG_INFO") << "Creating renderer...\n";
    this->renderer = new Renderer(options.windowTitle, options.width, options.height, options.alias, this);
    LOG(INFO, "LOG_INFO") << "Creating script manager...\n";
    this->scriptManager = new ScriptManager(renderer, this);
}

int LARE::Tick(Scene* scene){
    return this->renderer->UpdateScene(scene);
}

void LARE::captureMouse(){
    glfwSetInputMode(renderer->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void LARE::keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods){
    currentLareInstance->getScriptMan()->updateScriptKeys(key);
}

void LARE::mouseCallback(GLFWwindow* win, double xPos, double yPos){
    currentLareInstance->mousePosition = Vector2(xPos, yPos);
}

LARE::~LARE(){
    delete renderer;
}

} // LARE