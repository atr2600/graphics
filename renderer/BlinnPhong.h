//
// Created by brand on 3/4/2019.
//

#ifndef OPENGL_FCG_BLINNPHONG_H
#define OPENGL_FCG_BLINNPHONG_H


#include "../src/Vector3D.h"
#include "Shader.h"
#include <map>
using namespace sivelab;

class BlinnPhong : public Shader {

protected:

    Vector3D diffuse, specular;
    float phongExp;

public:
    BlinnPhong(const Vector3D &diffuse, const Vector3D &specular, float phongExp);

    bool VisibilityQuery(Ray r, double tmin, double tmax, std::vector<Shape *> &shapes);
    sivelab::Vector3D applyShader(Ray &r, std::vector<Light *> &lights, std::vector<Shape *> &shapes, HitStruct &h, std::map<std::string, Shader*> &shaders, double softX, double softY);


};


#endif //OPENGL_FCG_BLINNPHONG_H
