#include <Transform.hpp>

namespace LARE{

Vector2::Vector2(){
    this->x = 0.0f;
    this->y = 0.0f;
}

Vector2::Vector2(float x, float y){
    this->x = x;
    this->y = y;
}

Vector3::Vector3(){
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

Vector3::Vector3(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

} // LARE