//
// Created by brand on 2/27/2019.
//

#ifndef OPENGL_FCG_LAMBERTIAN_H
#define OPENGL_FCG_LAMBERTIAN_H


#include "Shader.h"
#include "../src/Vector3D.h"
#include <map>
class Lambertian : public Shader {

public:
    Lambertian(sivelab::Vector3D thisColor);


    bool VisibilityQuery(Ray r, double tmin, double tmax, std::vector<Shape *> &shapes);

    sivelab::Vector3D applyShader(Ray &r, std::vector<Light *> &lights, std::vector<Shape *> &shapes, HitStruct &h , std::map<std::string, Shader*> &shaders);

};




#endif //OPENGL_FCG_LAMBERTIAN_H
