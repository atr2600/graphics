//
// Created by brand on 3/4/2019.
//

#ifndef OPENGL_FCG_BOX_H
#define OPENGL_FCG_BOX_H


#include "../src/Vector3D.h"
#include "Triangle.h"
#include "Shape.h"

/**
 * Box class.
 */
class Box : public Shape {
    /**
     * Turning 2 points into 8 points. Turning those 8 points into 12 triangles.
     */
public:
    Triangle *getTriangles();

private:
    sivelab::Vector3D minPt, maxPt;
    Triangle triangles[12];
    sivelab::Vector3D pts[8];
public:
    Box(sivelab::Vector3D minPt, sivelab::Vector3D maxPt);
    bool intersect(double tmin, double &tmax, HitStruct &hit, Ray r);

};


#endif //OPENGL_FCG_BOX_H
