//
// Created by brand on 2/27/2019.
//

#ifndef OPENGL_FCG_LAMBERTIAN_H
#define OPENGL_FCG_LAMBERTIAN_H


#include "Shader.h"
#include "../src/Vector3D.h"

class Lambertian : public Shader {

public:
    Lambertian(sivelab::Vector3D thisColor);
};


#endif //OPENGL_FCG_LAMBERTIAN_H
