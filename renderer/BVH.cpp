//
// Created by khan on 4/6/19.
//

#include <algorithm>
#include "BVH.h"

BVH::BVH(Shape *s) {

}

BVH::BVH(std::vector<BVH *> shapes, int h) {
    //Check size for 1 or 2
    // Then you can just set the child to left and right
    // this is the osrt section
    std::sort(shapes,h%3);

    if(shapes.size()!=1){
        leftChild = new BVH(&shapes[0]);
        rightChild = new BVH(&shapes.size()/2);
    }

    //set min mid max variables
    //lowest low and highest max of left and right child.
    setXdim(sivelab::Vector3D(shapes[0]->getXdim()));
    setYdim(sivelab::Vector3D(shapes[0]->getYdim()));
    setZdim(sivelab::Vector3D(shapes[0]->getZdim()));
    for(int i = 0; i<shapes.size();i++){
        if(getXdim()[0]>shapes[i]->getXdim()[0]){
            xdim[0] = getXdim()[0];
        }
        if(getXdim()[2]<shapes[i]->getXdim()[2]){
            xdim[2] = getXdim()[2];
        }
        if(getYdim()[0]>shapes[i]->getYdim()[0]){
            xdim[0] = getYdim()[0];
        }
        if(getYdim()[2]<shapes[i]->getYdim()[2]){
            xdim[2] = getYdim()[2];
        }
        if(getZdim()[0]>shapes[i]->getZdim()[0]){
            xdim[0] = getZdim()[0];
        }
        if(getZdim()[2]<shapes[i]->getZdim()[2]){
            xdim[2] = getZdim()[2];
        }
    }
    xdim[1] = xdim[2]-xdim[0];
    ydim[1] = ydim[2]-ydim[0];
    zdim[1] = zdim[2]-zdim[0];

}

bool BVH::intersect(double tmin, double &tmax, HitStruct &hit, Ray r) {
    double tmin, tmax, txmin, txmax, tymin, tymax, tzmin, tzmax;
    


    if(r.getDirection()[0] >= 0){
        txmin = (xdim[0]-r.getOrigin()[0])/r.getDirection()[0];
        txmax = (xdim[2]-r.getOrigin()[0])/r.getDirection()[0];
    } else {
        txmin = (xdim[2]-r.getOrigin()[0])/r.getDirection()[0];
        txmax = (xdim[0]-r.getOrigin()[0])/r.getDirection()[0];
    }
    if(r.getDirection()[1] >= 0){
        tymin = (ydim[0]-r.getOrigin()[1])/r.getDirection()[1];
        tymax = (ydim[2]-r.getOrigin()[1])/r.getDirection()[1];
    } else {
        tymin = (ydim[2]-r.getOrigin()[1])/r.getDirection()[1];
        tymax = (ydim[0]-r.getOrigin()[1])/r.getDirection()[1];
    }
    if(r.getDirection()[1] >= 0){
        tzmin = (zdim[0]-r.getOrigin()[2])/r.getDirection()[2];
        tzmax = (zdim[2]-r.getOrigin()[2])/r.getDirection()[2];
    } else {
        tzmin = (zdim[2]-r.getOrigin()[2])/r.getDirection()[2];
        tzmax = (zdim[0]-r.getOrigin()[2])/r.getDirection()[2];
    }
}

const sivelab::Vector3D &BVH::getXdim() const {
    return xdim;
}

void BVH::setXdim(const sivelab::Vector3D &xdim) {
    BVH::xdim = xdim;
}

const sivelab::Vector3D &BVH::getYdim() const {
    return ydim;
}

void BVH::setYdim(const sivelab::Vector3D &ydim) {
    BVH::ydim = ydim;
}

const sivelab::Vector3D &BVH::getZdim() const {
    return zdim;
}

void BVH::setZdim(const sivelab::Vector3D &zdim) {
    BVH::zdim = zdim;
}

