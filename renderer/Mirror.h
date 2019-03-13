//
// Created by brand on 3/4/2019.
//

#include <map>
#include "Shader.h"

#ifndef OPENGL_FCG_MIRROR_H
#define OPENGL_FCG_MIRROR_H


class Mirror : public Shader {
public:
    int limit = 2;
    int count = 0;
    Mirror();

    bool VisibilityQuery(Ray r, double tmin, double tmax, std::vector<Shape *> &shapes){}


    sivelab::Vector3D reflection(Ray r, double tmin, double &tmax, std::vector<Shape *> &shapes, std::map<std::string, Shader*> &shaders, std::vector<Light *> &lights);
    sivelab::Vector3D applyShader(Ray &r, std::vector<Light *> &lights, std::vector<Shape *> &shapes, HitStruct &h, std::map<std::string, Shader*> &shaders );
};


#endif //OPENGL_FCG_MIRROR_H





