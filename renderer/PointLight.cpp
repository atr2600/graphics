//
// Created by brand on 2/5/2019.
//

#include "PointLight.h"



PointLight::PointLight(sivelab::Vector3D position, sivelab::Vector3D intensity)
        : Light(position, intensity) {
    setHeight(0.0);
    setWidth(0.0);
    setNormal(sivelab::Vector3D(0,0,0));
}



/**
 * Function that will bring light to the objects. :D
 * @param point
 * @param lightDirction
 * @param distance
 */
void PointLight::lightItUp(sivelab::Vector3D &point, sivelab::Vector3D &lightDirction, float &distance) const {
    //Taking the point that needs to be shaded and subtracting the position of the light.
    lightDirction = (point - getPosition());
    float r2 = lightDirction.normalize();
    distance = (r2*r2);
    lightDirction /= distance;
}