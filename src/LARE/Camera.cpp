#include <Camera.hpp>
#include <Scripting.hpp>

namespace LARE{

Camera::Camera(std::string name) : Object(name){
    camData = CameraData{};
    pAngle = 0;
    front = Vector3(0.0f, 0.0f, -1.0f);
    up = Vector3(0.0f, 1.0f, 0.0f);
}

void Camera::initScript(){
    this->script->init(this);
}

void Camera::updateScript(){
    this->script->update(this);
}

void Camera::offsetFB(float speed){
    position = Transform::glmToInternal(Transform::internalToGLM(position) + (speed * Transform::internalToGLM(front)));
}

void Camera::offsetLR(float speed){
    position = Transform::glmToInternal(Transform::internalToGLM(position) + glm::cross(Transform::internalToGLM(front), Transform::internalToGLM(up)) * speed);
}

void Camera::update(){
    // Update cam stuff
    camData.model = glm::mat4(1.0f);//glm::rotate(glm::mat4(0.5f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    camData.view = glm::lookAt(Transform::internalToGLM(position), Transform::internalToGLM(position) + glm::normalize(Transform::internalToGLM(front)), Transform::internalToGLM(up));
    // Script
    updateScript();
}

} // LARE