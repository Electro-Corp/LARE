#include <Object.hpp>
#include <Scripting.hpp>

namespace LARE{

Object::Object(std::string name){
    this->name = name;
    this->type = ObjectType::MESH; // Default

    // Transform
    this->transform = Transform();
}

void Object::initScript(){
    this->script->init(this);
}

void Object::updateScript(){
    this->script->update(this);
}

void Object::update(){
    updateScript();
}

} // LARE