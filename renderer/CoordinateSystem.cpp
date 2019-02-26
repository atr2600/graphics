//
// Created by brand on 2/12/2019.
//

#include "CoordinateSystem.h"

CoordinateSystem::CoordinateSystem(){

}
CoordinateSystem::CoordinateSystem(sivelab::Vector3D direction, sivelab::Vector3D temp){

    W = (-1*direction)/direction.length();
    W.normalize();
    U = temp.cross(W)/temp.cross(W).length();
    U.normalize();
    V = W.cross(U);
    V.normalize();

}

const sivelab::Vector3D &CoordinateSystem::getU() const {
    return U;
}

const sivelab::Vector3D &CoordinateSystem::getV() const {
    return V;
}

const sivelab::Vector3D &CoordinateSystem::getW() const {
    return W;
}
