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
    };

    class Transform{
    private:
    public:
        glm::mat4 transform;

        Transform(){
            transform = glm::mat4(1.0f);
        }

        void Scale(Vector3 newScale){
            transform = glm::scale(transform, glm::vec3(newScale.x, newScale.y, newScale.z));
        }

        void Rotate(float angle, Vector3 axis){
            transform = glm::rotate(transform, glm::radians(angle), glm::vec3(axis.x, axis.y, axis.z));   
        }
    };
}