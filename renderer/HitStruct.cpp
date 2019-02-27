//
// Created by brand on 2/26/2019.
//

#include "HitStruct.h"

void HitStruct::setNorm(const sivelab::Vector3D &norm) {
    HitStruct::norm = norm;
}

void HitStruct::setPointInterect(const sivelab::Vector3D &pointInterect) {
    HitStruct::pointInterect = pointInterect;
}

void HitStruct::setActualT(float actualT) {
    HitStruct::actualT = actualT;
}
