//
// Created by brand on 2/26/2019.
//

#pragma once

#include "../src/Vector3D.h"
#include "../renderer/Shape.h"

class Triangle : public Shape {
private:
    sivelab::Vector3D v0,v1,v2;
public:
    void setV0(const sivelab::Vector3D &v0);

    void setV1(const sivelab::Vector3D &v1);

    void setV2(const sivelab::Vector3D &v2);

public:
    Triangle();

    Triangle(sivelab::Vector3D v0, sivelab::Vector3D v1, sivelab::Vector3D v2);

    bool intersect(double tmin, double tmax, HitStruct hit, Ray r);

};

