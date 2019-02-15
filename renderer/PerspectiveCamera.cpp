//
// Created by brand on 2/5/2019.
//

#include "PerspectiveCamera.h"


void PerspectiveCamera::generateRay(int i, int j, Ray &r) {

    r.setOrigin(position);
    r.setDirection((focalLength * csys.getW() + csys.getU() * csys.getV()));
//    r.origin = position;
//    r.direction = focalLength * csys.getW() + csys.getU() * csys.getV();
}