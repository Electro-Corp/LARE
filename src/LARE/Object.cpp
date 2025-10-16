#include <Object.hpp>

namespace LARE{

Object::Object(std::string name){
    this->name = name;
    this->type = ObjectType::MESH; // Default

    // Transform
    this->transform = Transform();
}

} // LARE