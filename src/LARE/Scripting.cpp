#include <Scripting.hpp>

namespace LARE{

Script::Script(lua_State* state, std::string sourceLocation, Object* gm){
    this->luaState = state;
    this->gm = gm;
    keyback = 0;
    // Load the script
    int scriptLoadStatus = luaL_dofile(state, sourceLocation.c_str());
    if(scriptLoadStatus != 0){
        LOG(ERROR, "LOG_ERROR") << "Failed to load script " << sourceLocation << ", error: " << lua_tostring(luaState, -1) << "\n";
        lua_pop(state, 1);
    }
    // Make sure init and update exist
    assert(luabridge::getGlobal(luaState, "init").isNil() != true);
    assert(luabridge::getGlobal(luaState, "update").isNil() != true);

    // Input update
    if(!luabridge::getGlobal(luaState, "onKeyPressed").isNil()){
        keyback = 1;
    }
}


ScriptManager::ScriptManager(Renderer* rendererPtr){
    // Get globals to expose to Lua
    this->rendererGlob = std::unique_ptr<Renderer>(rendererPtr);
}

Script* ScriptManager::initScript(std::string path, Object* root){
    LOG(INFO, "LOG_INFO") << "Loading script " << path << " on object "<< root->getName() << "...\n";
    // Init a lua statee
    lua_State* tmp = nullptr;
    tmp = luaL_newstate();
    luaL_openlibs(tmp);
    exposeLAREToScript(tmp);

    Script* s = new Script(tmp, path, root);
    this->scripts.push_back(s);

    return s;
}

void ScriptManager::exposeLAREToScript(lua_State* luaState){
    LOG(INFO, "LOG_INFO") << "Scriptmanager is exposing the engine to Lua...\n";

    // Expose Vector3
    luabridge::getGlobalNamespace(luaState)
        .beginClass<Vector3>("Vector3")
        .addConstructor<void(*) (float, float, float)>()
        .addProperty("x", &Vector3::x)
        .addProperty("y", &Vector3::y)
        .addProperty("z", &Vector3::z)
        .endClass();
    // Expose Transform
    luabridge::getGlobalNamespace(luaState)
        .beginClass<Transform>("Transform")
        //.addConstructor<void(*)>()
        .addProperty("transform", &Transform::transform)
        .addFunction("Scale", &Transform::Scale)
        .addFunction("Rotate", &Transform::Rotate)
        .addFunction("Translate", &Transform::Translate)
        .endClass();
    // Expose Camera
    luabridge::getGlobalNamespace(luaState)
        .beginClass<Camera>("Camera")
        .addProperty("position", &Camera::position)
        .addProperty("pAngle", &Camera::pAngle)
        .endClass();
    // Expose Object and light
    luabridge::getGlobalNamespace(luaState)
        .beginClass<Object>("Object")
        .addProperty("transform", &Object::transform)
        .addProperty("shaderProgram", &Object::shaderProgram)
        .endClass()
        .deriveClass<Light, Object>("Light")
        .addProperty("ambient", &Light::color)
        .addProperty("specular", &Light::specular)
        .addProperty("diffuse", &Light::diffuse)
        .endClass();
    
    LOG(INFO, "LOG_INFO") << "Exposing finished...\n";
}

void ScriptManager::updateScriptKeys(int key){
    for(auto& script : scripts){
        if(script->keyback){
            // Is it normal
            if(key >= 39 && key <=92){
                script->keypressed(script->gm, glfwGetKeyName(key, 0));
            }else{
                switch(key){
                    default:
                        script->keypressed(script->gm, "UnknownKey");
                        break;
                }
            }
        }
    }
}

} // LARE