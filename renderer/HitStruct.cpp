//
// Created by brand on 2/26/2019.
//

#include "HitStruct.h"

/**
 * Returns the norm.
 * @param norm
 */
void HitStruct::setNorm(const sivelab::Vector3D &norm) {
    HitStruct::norm = norm;
}

/**
 *
 * @param pointInterect
 */
void HitStruct::setPointInterect(const sivelab::Vector3D &pointInterect) {
    HitStruct::pointInterect = pointInterect;
}

/**
 *
 * @param actualT
 */
void HitStruct::setActualT(float actualT) {
    HitStruct::actualT = actualT;
}
