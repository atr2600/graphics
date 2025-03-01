//
// Created by brand on 2/12/2019.
//

#include "Ray.h"
#include"../src/Vector3D.h"


/**
 *
 * @param direction
 */
void Ray::setDirection(const sivelab::Vector3D &direction) {
    Ray::direction = direction;
}

/**
 *
 * @param origin
 */
void Ray::setOrigin(const sivelab::Vector3D &origin) {
    Ray::origin = origin;
}



Ray::Ray(){}

/**
 *
 * @param direction
 * @param origin
 */
Ray::Ray(const sivelab::Vector3D &direction, const sivelab::Vector3D &origin) : direction(direction), origin(origin) {
    invdir = -1 * direction;
    sign[0] = (invdir[0] < 0);
    sign[1] = (invdir[1] < 0);
    sign[2] = (invdir[2] < 0);
}

/**
 *
 * @return
 */
const sivelab::Vector3D &Ray::getDirection() const {
    return direction;
}

/**
 *
 * @return
 */
const sivelab::Vector3D &Ray::getOrigin() const {
    return origin;
}

