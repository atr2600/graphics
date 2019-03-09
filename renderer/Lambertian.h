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

    sivelab::Vector3D applyShader(Ray &r, std::vector<Light *> &lights, std::vector<Shape *> &shapes, HitStruct &h );

};




#endif //OPENGL_FCG_LAMBERTIAN_H
