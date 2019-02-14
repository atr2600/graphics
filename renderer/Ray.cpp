//
// Created by brand on 2/12/2019.
//

#include "Ray.h"

void Ray::setDirection(const sivelab::Vector3D &direction) {
    Ray::direction = direction;
}

void Ray::setOrigin(const sivelab::Vector3D &origin) {
    Ray::origin = origin;
}
