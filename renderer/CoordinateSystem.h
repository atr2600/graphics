//
// Created by brand on 2/12/2019.
//

#pragma once

#include <vector>
#include"../src/Vector3D.h"


class CoordinateSystem {
private:

    sivelab::Vector3D U = sivelab::Vector3D(1,0,0);
    sivelab::Vector3D V = sivelab::Vector3D(0,1,0);
    sivelab::Vector3D W = sivelab::Vector3D(0,0,1);


public:
    const sivelab::Vector3D &getU() const;

    const sivelab::Vector3D &getV() const;

    const sivelab::Vector3D &getW() const;

public:
    CoordinateSystem();
    CoordinateSystem(sivelab::Vector3D direction, sivelab::Vector3D temp);
};

