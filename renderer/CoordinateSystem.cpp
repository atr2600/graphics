//
// Created by brand on 2/12/2019.
//

#include "CoordinateSystem.h"

CoordinateSystem::CoordinateSystem(){

}
CoordinateSystem::CoordinateSystem(sivelab::Vector3D direction, sivelab::Vector3D temp){

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
