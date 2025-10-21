/*  
    File for managing Lua scripting
*/
#pragma once

#include <Transform.hpp>
#include <Camera.hpp>
#include <Light.hpp>
#include <Renderer.hpp>

#include <string>

extern "C"
{
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include <LuaBridge/LuaBridge.h>
#include <LuaBridge/detail/LuaRef.h>
#include <aixlog.hpp>

namespace LARE{
    class Script{
    private:
        lua_State* luaState;

    public:
        Object* gm;

        Script(lua_State* state, std::string sourceLocation, Object* gm);

        lua_State* getState(){
            return this->luaState;
        }

        template <typename T>
        void update(T* cast){
            luabridge::LuaRef updateFunc = luabridge::getGlobal(luaState, "update");
            updateFunc((T*)gm);
        }

        template <typename T>
        void init(T* cast){
            luabridge::LuaRef initFunc = luabridge::getGlobal(luaState, "init");;
            initFunc((T*)gm);
        }

    };

    class ScriptManager{
    private:
        std::unique_ptr<Renderer> rendererGlob;
    public:
        ScriptManager(Renderer* rendererPtr);

        Script* initScript(std::string path, Object* root);

        void exposeLAREToScript(lua_State* luaState);
    };
}  // LARE

