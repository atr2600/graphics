//
// Created by khan on 4/6/19.
//

#ifndef OPENGL_FCG_BVH_H
#define OPENGL_FCG_BVH_H


#include <vector>
#include "Shape.h"

class BVH : public Shape {
private:
    sivelab::Vector3D xdim, ydim, zdim; //[0]=min; [1]= mid; [2] = max
public:
    Shape * leftChild, rightChild;

    BVH(std::vector<* BVH> shapes, int h);

    BVH( Shape * s);

    bool intersect(double tmin, double &tmax, HitStruct &hit, Ray r);

    const sivelab::Vector3D &getXdim() const;

    void setXdim(const sivelab::Vector3D &xdim);

    const sivelab::Vector3D &getYdim() const;

    void setYdim(const sivelab::Vector3D &ydim);

    const sivelab::Vector3D &getZdim() const;

    void setZdim(const sivelab::Vector3D &zdim);


};


#endif //OPENGL_FCG_BVH_H
