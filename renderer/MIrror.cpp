//
// Created by brand on 3/4/2019.
//

#include "MIrror.h"
#include <map>

sivelab::Vector3D Mirror::applyShader(Ray &r, std::vector<Light *> &lights, std::vector<Shape *> &shapes,
                                      HitStruct &h, std::map<std::string, Shader*> &shaders) {
    using namespace sivelab;
    int count = 10;
    int tmax = 999999;
    Ray newRay(h.getNorm(),(h.getPointInterect() + (h.getNorm() * 0.001)));
    return reflection(newRay, 0.0001, tmax, shapes,shaders ,lights);

}



sivelab::Vector3D Mirror::reflection(Ray r, double tmin, double tmax, std::vector<Shape *> &shapes,std::map<std::string, Shader*> &shaders, std::vector<Light *> &lights){

    using namespace sivelab;
    HitStruct h;
    for(int i = 0; i<shapes.size();i++){
        if(shapes[i]->intersect(tmin,tmax, h,r)) {
            return shaders.at(shapes[i]->getColor())->applyShader(r,lights,shapes,h,shaders);
        };
    }

    return Vector3D(0,0,0);

}


Mirror::Mirror() {}
