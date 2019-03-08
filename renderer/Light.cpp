//
// Created by brand on 2/5/2019.
//

#include "Light.h"
#include "../src/Vector3D.h"


const sivelab::Vector3D &Light::getPosition() const {
    return position;
}

void Light::setPosition(const sivelab::Vector3D &position) {
    Light::position = position;
}

const sivelab::Vector3D &Light::getIntensity() const {
    return intensity;
}

void Light::setIntensity(const sivelab::Vector3D &intensity) {
    Light::intensity = intensity;
}
