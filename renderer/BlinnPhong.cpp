//
// Created by brand on 3/4/2019.
//

#include "BlinnPhong.h"
#include <math.h>
#include <cfloat>
#include <map>

sivelab::Vector3D BlinnPhong::applyShader(Ray &r, std::vector<Light *> &lights, std::vector<Shape *> &shapes, HitStruct &h, std::map<std::string, Shader*> &shaders, double softX, double softY){
    sivelab::Vector3D newColor(0,0,0);
    sivelab::Vector3D intensity;

    for(int i = 0; i < lights.size(); i++) {
        sivelab::Vector3D lightP = lights[i]->getPosition();
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
        sivelab::Vector3D H = (lightDir + (r.getDirection()) * -1);
        H.normalize();
        sivelab::Vector3D Ks = specular * pow(std::max(normal.dot(H), 0.0), phongExp)*lights[i]->getIntensity();

        if(!VisibilityQuery(sRay, 0.0001, DBL_MAX , shapes)){
            newColor += intensity * getColor() * sivelab::Vector3D(1, 1, 1);
            newColor = newColor.clamp(0.0,1.0);
            newColor += Ks;
        }
    }

    return newColor.clamp(0,1);

}


BlinnPhong::BlinnPhong(const Vector3D &diffuse, const Vector3D &specular, float phongExp) : diffuse(diffuse),
                                                                                            specular(specular),
                                                                                            phongExp(phongExp) {
    setColor(diffuse);
}


bool BlinnPhong::VisibilityQuery(Ray r, double tmin, double tmax, std::vector<Shape *> &shapes){

    HitStruct h;
    for(int i = 0; i<shapes.size();i++){
        if(shapes[i]->intersect(tmin,tmax, h,r)) return true;
    }
    return false;

}