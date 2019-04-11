//
// Created by brand on 3/4/2019.
//

#include "Mirror.h"
#include <map>
#include <cfloat>


sivelab::Vector3D Mirror::applyShader(Ray &r, std::vector<Light *> &lights,
                                      HitStruct &h, std::map<std::string, Shader*> &shaders, double softX, double softY, BVH *boxes) {

    using namespace sivelab;
    int count = 10;
    double max = DBL_MAX;
    Vector3D newDir = r.getDirection()-2*(r.getDirection().dot(h.getNorm()))*h.getNorm();
    Ray newRay(newDir,(h.getPointInterect() + (newDir * 0.001)));

    return reflection(newRay, 0.0001, max,boxes,shaders ,lights);

}



sivelab::Vector3D Mirror::reflection(Ray r, double tmin, double &tmax,BVH *boxes,std::map<std::string, Shader*> &shaders, std::vector<Light *> &lights){

    using namespace sivelab;
    HitStruct h;
    Vector3D rgb(0,0,0);
    double empty = 0;
    double max = DBL_MAX;

        if(boxes->intersect(0.006,max,h,r)){
            if(h.getActualT()<max){
                max = h.getActualT();
                rgb = shaders.at(h.shader)->applyShader(r, lights, h, shaders,0,0, boxes);
            }
        }

    return rgb;

}


Mirror::Mirror() {}
