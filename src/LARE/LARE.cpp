#include <LARE.hpp>

namespace LARE{

LARE::LARE(EngineOptions options){
    // Init logging
    AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace);
    LOG(INFO, "LOG_TAG") << "LARE Starting...\n";
    LOG(INFO, "LOG_TAG") << "Creating renderer...\n";
    this->renderer = new Renderer(options.windowTitle, options.width, options.height, options.alias);
}

int LARE::Tick(Scene* scene){
    return this->renderer->UpdateScene(scene);
}

LARE::~LARE(){
    delete renderer;
}

} // LARE