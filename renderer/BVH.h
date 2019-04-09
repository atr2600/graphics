//
// Created by khan on 4/6/19.
//

#ifndef OPENGL_FCG_BVH_H
#define OPENGL_FCG_BVH_H


#include <vector>
#include <boost/exception/detail/shared_ptr.hpp>
#include "Shape.h"
#include "Sphere.h"
#include "Triangle.h"

class BVH : public Shape {
public:
    HitStruct lhit,rhit;

    BVH(std::vector<Shape *> BVHs, int h);

    bool intersect(double tmin, double &tmax, HitStruct &hit, Ray r);


    void minOrMax(Shape *l, Shape*r);

    static bool compareItX(Shape * a, Shape * b) {
        return a->xdim[1] < a->xdim[1];
    }

    static bool compareItY(Shape * a, Shape * b) {
        return a->ydim[1] < a->ydim[1];
    }

    static bool compareItZ(Shape * a, Shape * b) {
        return a->zdim[1] < a->zdim[1];
    }



};


#endif //OPENGL_FCG_BVH_H
