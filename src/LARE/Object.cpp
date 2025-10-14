#include <Object.hpp>

namespace LARE{

Object::Object(std::string name){
    this->name = name;

    // Transform
    this->transform = Transform();
}

} // LARE