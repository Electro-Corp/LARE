#include <Camera.hpp>
#include <Scripting.hpp>

namespace LARE{

Camera::Camera(std::string name) : Object(name){
    camData = CameraData{};
    pAngle = 0;
    front = Vector3(0.0f, 0.0f, -1.0f);
}

void Camera::initScript(){
    this->script->init(this);
}

void Camera::updateScript(){
    this->script->update(this);
}

void Camera::update(){
    // Update cam stuff
    camData.model = glm::mat4(1.0f);//glm::rotate(glm::mat4(0.5f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    
    camData.view = glm::lookAt(Transform::internalToGLM(position), Transform::internalToGLM(position) + glm::normalize(Transform::internalToGLM(front)), glm::vec3(0.0f, 1.0f, 0.0f));
    // Script
    updateScript();
}

} // LARE