//
// Created by brand on 3/4/2019.
//

#include "Mirror.h"
#include <map>
#include <cfloat>

sivelab::Vector3D Mirror::applyShader(Ray &r, std::vector<Light *> &lights, std::vector<Shape *> &shapes,
                                      HitStruct &h, std::map<std::string, Shader*> &shaders) {
    using namespace sivelab;
    int count = 10;
    double max = DBL_MAX;
    Vector3D newDir = r.getDirection()-2*(r.getDirection().dot(h.getNorm()))*h.getNorm();
    Ray newRay(newDir,(h.getPointInterect() + (newDir * 0.001)));
    return reflection(newRay, 0.0001, max, shapes,shaders ,lights);

}



sivelab::Vector3D Mirror::reflection(Ray r, double tmin, double &tmax, std::vector<Shape *> &shapes,std::map<std::string, Shader*> &shaders, std::vector<Light *> &lights){

    using namespace sivelab;
    HitStruct h;
    Vector3D rgb(0,0,0);
    for(int i = 0; i<shapes.size();i++){
        if(shapes[i]->intersect(0.05,tmax, h,r)) {
            if(shapes[i]->getTvalue()<=tmax){
                tmax = shapes[i]->getTvalue();
                rgb = shaders.at(shapes[i]->getColor())->applyShader(r,lights,shapes,h,shaders);

            }
        }
    }

    return rgb;

}


Mirror::Mirror() {}
