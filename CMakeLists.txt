cmake_minimum_required(VERSION 3.15)
project(LARE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g -fno-math-errno -fno-trapping-math")

set(BUILD_WSI_XLIB_SUPPORT OFF)

# Lua
find_package(Lua REQUIRED)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src/LARE
    ${CMAKE_SOURCE_DIR}/thirdPartyInc
    /usr/local/include 
    ${LUA_INCLUDE_DIR}
)

set(SOURCES
    # Graphics
    src/LARE/Renderer.cpp
    src/LARE/Shader.cpp
    src/LARE/Skybox.cpp
    src/LARE/Camera.cpp
    # Engine
    src/LARE/Scripting.cpp
    src/LARE/Transform.cpp
    src/LARE/Scene.cpp
    src/LARE/Object.cpp
    # Light
    src/LARE/Light.cpp
    # Mesh and Model
    src/LARE/Mesh.cpp
    src/LARE/Model.cpp
    # LARE
    src/LARE/LARE.cpp
    # GLAD
    thirdPartyInc/glad.c

    # Test program
    src/main.cpp
)

# Add executable
add_executable(LARE ${SOURCES})

target_link_libraries(LARE
    glfw
    GL 
    X11
    pthread
    Xrandr
    Xi
    dl
    assimp
    ${LUA_LIBRARIES} 
    ${LUA_DEPENDENCIES}
)