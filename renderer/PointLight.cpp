//
// Created by brand on 2/5/2019.
//

#include "PointLight.h"

PointLight::PointLight() {}


PointLight::PointLight(sivelab::Vector3D position, sivelab::Vector3D intensity){
    setPosition(position);
    setIntensity(intensity);
}