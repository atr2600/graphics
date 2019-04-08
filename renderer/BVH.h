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
    Shape * leftChild;
    Shape * rightChild;

    Vector3D bounds[2];

    BVH(std::vector<Shape *> BVHs, int h);

    BVH( Shape * s);

    bool intersect(double tmin, double &tmax, HitStruct &hit, Ray r);

    void setValues(Shape * child, std::vector<Shape *> tree);

    void minOrMax(Shape *l, Shape*r);

};


#endif //OPENGL_FCG_BVH_H
