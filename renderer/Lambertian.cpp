//
// Created by brand on 2/27/2019.
//

#include "Lambertian.h"
#include <algorithm>
#include <cfloat>
#include <map>
#include "Light.h"
#include "AreaLight.h"
#include "PointLight.h"

Lambertian::Lambertian(sivelab::Vector3D thisColor){
    setColor(thisColor);
}


sivelab::Vector3D Lambertian::applyShader(Ray &r, std::vector<Light *> &lights, HitStruct &h, std::map<std::string, Shader*> &shaders, double softX, double softY, BVH *boxes){
    sivelab::Vector3D newColor(0,0,0);
    sivelab::Vector3D intensity;

    //passing in the array.



    for(int i = 0; i < lights.size(); i++) {
        sivelab::Vector3D lightP;
        lightP = lights[i]->getPosition();

        if(lights[i]->getName() == "area"){
            float y = lights[i]->getHeight();
            float x = lights[i]->getWidth();
            lightP[0] += -(x/2) + (x)*softX;
            lightP[2] += (-y/2) + (y)*softY;
        }

        sivelab::Vector3D hP = h.getPointInterect();
        sivelab::Vector3D lightDir(lightP[0] - hP[0], lightP[1] - hP[1], lightP[2] - hP[2]);
        sivelab::Vector3D shadowDir(lightP[0] - hP[0], lightP[1] - hP[1], lightP[2] - hP[2]);

        lightDir.normalize();
        sivelab::Vector3D normal = h.getNorm();
        normal.normalize();
        intensity = lights[i]->getIntensity()*std::max(0.0f, (float) normal.dot(lightDir));

        sivelab::Vector3D testHp = hP + (shadowDir * 0.0001);
        Ray sRay = Ray(shadowDir, testHp);


        if(!VisibilityQuery(sRay, 0.0001, DBL_MAX , boxes)){
            newColor += intensity * getColor() * sivelab::Vector3D(1, 1, 1);
            newColor = newColor.clamp(0.0,1.0);
        }
    }
    return newColor;
}

bool Lambertian::VisibilityQuery(Ray r, double tmin, double tmax, BVH *boxes){

    HitStruct h;
    return boxes->intersect(tmin, tmax, h, r);
}