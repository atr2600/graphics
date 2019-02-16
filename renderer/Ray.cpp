//
// Created by brand on 2/12/2019.
//

#include "Ray.h"
#include"../src/Vector3D.h"

void Ray::setDirection(const sivelab::Vector3D &direction) {
    Ray::direction = direction;
}

void Ray::setOrigin(const sivelab::Vector3D &origin) {
    Ray::origin = origin;
}



Ray::Ray(){}

Ray::Ray(const sivelab::Vector3D &direction, const sivelab::Vector3D &origin) : direction(direction), origin(origin) {}

const sivelab::Vector3D &Ray::getDirection() const {
    return direction;
}

const sivelab::Vector3D &Ray::getOrigin() const {
    return origin;
}

