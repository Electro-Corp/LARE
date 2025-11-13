#include <LARE.hpp>

namespace LARE{

LARE::LARE(EngineOptions options){
    // Init logging
    AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace);
    LOG(INFO, "LOG_INFO") << "LARE Starting... (compiled on " << __DATE__ << " @ " << __TIME__ << ")\n";
    LOG(INFO, "LOG_INFO") << "Creating renderer...\n";
    this->renderer = new Renderer(options.windowTitle, options.width, options.height, options.alias);
    LOG(INFO, "LOG_INFO") << "Creating script manager...\n";
    this->scriptManager = new ScriptManager(renderer);
}

int LARE::Tick(Scene* scene){
    return this->renderer->UpdateScene(scene);
}

LARE::~LARE(){
    delete renderer;
}

} // LARE