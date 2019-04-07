//
// Created by khan on 4/6/19.
//

#include "AreaLight.h"




void AreaLight::lightItUp(sivelab::Vector3D &point, sivelab::Vector3D &lightDirction, float &distance) const {

    lightDirction = normal;

}


const CoordinateSystem &AreaLight::getLightxyz() const {
    return lightxyz;
}

void AreaLight::setLightxyz(const CoordinateSystem &lightxyz) {
    AreaLight::lightxyz = lightxyz;
}

AreaLight::AreaLight(const sivelab::Vector3D &position, const sivelab::Vector3D &intensity,
                     const sivelab::Vector3D &normal, float height, float width) : Light(position, intensity, normal,
                                                                                         height, width) {

    lightxyz = CoordinateSystem(normal,sivelab::Vector3D(0.0,0.0,-1.0));
    name = "area";

}
