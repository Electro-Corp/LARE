/*
    Light class that extends from Object
*/
#pragma once

#include <Object.hpp>

namespace LARE{
    class Light : public Object{
    private:
    public:
        Vector3 color, specular, diffuse;

        Light(Vector3 color, Vector3 specular, Vector3 diffuse);
    };
} // LARE