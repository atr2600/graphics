//
// Created by brand on 2/26/2019.
//

#pragma once

#include "../src/Vector3D.h"

class HitStruct {
    sivelab::Vector3D norm;
    sivelab::Vector3D pointInterect;
public:
    const sivelab::Vector3D &getPointInterect() const;

private:
public:
    const sivelab::Vector3D &getNorm() const;

private:
    float actualT;
public:
    void setNorm(const sivelab::Vector3D &norm);

    void setPointInterect(const sivelab::Vector3D &pointInterect);

    void setActualT(float actualT);

    float getActualT() const;
    //add shader pointer later


};



