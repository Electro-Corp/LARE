/*
    Transform objects (all in a header)
*/
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace LARE{
    // So you dont gotta type "glm::vec3" all the time..
    // now just do {x, y, z}
    struct Vector3{
        float x, y, z;

        Vector3();
        Vector3(float x, float y, float z);
    };

    class Transform{
    private:
    public:
        glm::mat4 transform;

        Transform(){
            transform = glm::mat4(1.0f);
        }

        void Scale(Vector3 newScale){
            transform = glm::scale(transform, Transform::internalToGLM(newScale));
        }

        void Rotate(float angle, Vector3 axis){
            transform = glm::rotate(transform, glm::radians(angle), Transform::internalToGLM(axis));   
        }

        void Translate(Vector3 offset){
            transform = glm::translate(transform, Transform::internalToGLM(offset));
        }

        glm::vec3 getPosition(){
            return glm::vec3(transform[3]);
        }

        static glm::vec3 internalToGLM(Vector3 vec){
            return glm::vec3(vec.x, vec.y, vec.z);
        }
    };
}