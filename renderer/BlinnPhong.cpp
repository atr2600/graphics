//
// Created by brand on 3/4/2019.
//

#include "BlinnPhong.h"
#include <math.h>
#include <cfloat>


sivelab::Vector3D BlinnPhong::applyShader(Ray &r, std::vector<Light *> &lights, std::vector<Shape *> &shapes, HitStruct &h ){
    sivelab::Vector3D newColor(0,0,0);

    int lightSize = lights.size();

    for(int i = 0; i < lights.size(); i++) {

        sivelab::Vector3D lightP = lights[i]->getPosition();
        sivelab::Vector3D hP = h.getPointInterect();
        //Yes, this is backwords because I wanted the negative direction/reverse direction.
        //Used light as the head minus hit intersect as the tail.

        sivelab::Vector3D lightDir(lightP[0] - hP[0], lightP[1] - hP[1], lightP[2] - hP[2]);
        sivelab::Vector3D shadowDir(lightP[0] - hP[0], lightP[1] - hP[1], lightP[2] - hP[2]);
        lightDir.normalize();
        sivelab::Vector3D normal = h.getNorm();
        normal.normalize();

        sivelab::Vector3D H = (lightDir + (r.getDirection()) * -1);
        H.normalize();

        double Ks = pow(std::max(normal.dot(H), 0.0), phongExp);

        sivelab::Vector3D testHp = hP + (shadowDir * 0.0001);
        Ray sRay = Ray(shadowDir, testHp);


        if(!VisibilityQuery(sRay, 0.0001, DBL_MAX , shapes)){
        newColor += (lights[i]->getIntensity() * getColor() *
                     std::max(0.0, normal.dot(lightDir)));
        newColor += specular * Ks;
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