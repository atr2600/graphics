//
// Created by brand on 2/26/2019.
//

#pragma once

#include "../src/Vector3D.h"

class Triangle {
private:
    sivelab::Vector3D v0,v1,v2;
public:
    Triangle();

    Triangle(const sivelab::Vector3D &v0, const sivelab::Vector3D &v1, const sivelab::Vector3D &v2);

};

