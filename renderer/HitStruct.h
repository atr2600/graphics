//
// Created by brand on 2/26/2019.
//

#pragma once

#include "../src/Vector3D.h"

class HitStruct {
    sivelab::Vector3D norm;
    sivelab::Vector3D pointInterect;
    float actualT;
public:
    void setNorm(const sivelab::Vector3D &norm);

    void setPointInterect(const sivelab::Vector3D &pointInterect);

    void setActualT(float actualT);
    //add shader pointer later


};



