//
// Created by brand on 2/5/2019.
//

#include "PerspectiveCamera.h"


void PerspectiveCamera::generateRay(int i, int j, Ray &r) {
    r.origin = position;
    r.direction = focalLength * csys.getW() + csys.getU() * csys.getV();
}