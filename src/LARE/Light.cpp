#include <Light.hpp>

namespace LARE{

Light::Light(Vector3 color, Vector3 specular, Vector3 diffuse) : Object("LIGHT") {
    this->color = color;
    this->specular = specular;
    this->diffuse = diffuse;

    this->type = ObjectType::LIGHT;
}

} // LARE