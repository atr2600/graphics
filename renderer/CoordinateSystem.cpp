//
// Created by brand on 2/12/2019.
//

#include "CoordinateSystem.h"

CoordinateSystem::CoordinateSystem(){

}

/**
 * Generates a coordinateSystem.
 * @param direction
 * @param temp
 */
CoordinateSystem::CoordinateSystem(sivelab::Vector3D direction, sivelab::Vector3D temp){

    temp = sivelab::Vector3D(0.0,1.0,0.0);


    W = (-1*direction)/direction.length();
    W.normalize();
    U = temp.cross(W)/temp.cross(W).length();
    U.normalize();
    V = U.cross(W);
    V.normalize();

}

/**
 * Returns the U vector
 * @return U
 */
const sivelab::Vector3D &CoordinateSystem::getU() const {
    return U;
}

/**
 * Returns the V vector.
 * @return V
 */
const sivelab::Vector3D &CoordinateSystem::getV() const {
    return V;
}

/**
 * Returns the W vectory.
 * @return W
 */
const sivelab::Vector3D &CoordinateSystem::getW() const {
    return W;
}
