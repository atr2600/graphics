//
// Created by brand on 2/5/2019.
//

#include "Light.h"
#include "../src/Vector3D.h"


/**
 *
 * @return
 */
const sivelab::Vector3D &Light::getPosition() const {
    return position;
}

/**
 *
 * @param position
 */
void Light::setPosition(const sivelab::Vector3D &position) {
    Light::position = position;
}

/**
 *
 * @return
 */
const sivelab::Vector3D &Light::getIntensity() const {
    return intensity;
}


/**
 *
 * @param intensity
 */
void Light::setIntensity(const sivelab::Vector3D &intensity) {
    Light::intensity = intensity;
}
