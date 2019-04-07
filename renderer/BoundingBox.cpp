//
// Created by khan on 4/7/19.
//

#include <cfloat>
#include "BoundingBox.h"
#include "../src/Vector3D.h"
#include "HitStruct.h"
#include "Ray.h"


BoundingBox::BoundingBox(){
    max = Vector3D(-DBL_MAX,-DBL_MAX,-DBL_MAX);
    min = Vector3D(DBL_MAX,DBL_MAX,DBL_MAX);
}

BoundingBox::BoundingBox(const Vector3D &min, const Vector3D &max) : min(min), max(max) {}

void BoundingBox::expandValue(double value) {
    min = Vector3D(min[0]-value, min[1]-value, min[2]-value);
    max = Vector3D(max[0]+value, max[1]+value, max[2]+value);
}

void BoundingBox::expand(Vector3D pnt) {
    min = min - pnt;
    max = max + pnt;
}

Vector3D BoundingBox::centerPoint() const {
    return (min + max) / 2.0;
}

//bool BoundingBox::intersect(double minimum, double &maximum, HitStruct &hit, Ray r,Shape * s) {
//    double tmin, tmax, txmin, txmax, tymin, tymax, tzmin, tzmax, txymin, txymax, txyzmax, txyzmin;
//
//
//    if(r.getDirection()[0] >= 0){
//        txmin = (min[0]-r.getOrigin()[0])/r.getDirection()[0];
//        txmax = (max[0]-r.getOrigin()[0])/r.getDirection()[0];
//    } else {
//        txmin = (max[0]-r.getOrigin()[0])/r.getDirection()[0];
//        txmax = (min[0]-r.getOrigin()[0])/r.getDirection()[0];
//    }
//    if(r.getDirection()[1] >= 0){
//        tymin = (min[1]-r.getOrigin()[1])/r.getDirection()[1];
//        tymax = (max[1]-r.getOrigin()[1])/r.getDirection()[1];
//    } else {
//        tymin = (max[1]-r.getOrigin()[1])/r.getDirection()[1];
//        tymax = (min[1]-r.getOrigin()[1])/r.getDirection()[1];
//    }
//
//    if((tymax < tymin)||(tmin>tymax)){
//        return false;
//    }
//
//    tmin = (tymin > tmin ? tymin:tmin);
//    tmax = (tymax < tmax ? tymax:tmax);
//
//    if(r.getDirection()[2] >= 0){
//        tzmin = (min[2]-r.getOrigin()[2])/r.getDirection()[2];
//        tzmax = (max[2]-r.getOrigin()[2])/r.getDirection()[2];
//    } else {
//        tzmin = (max[2]-r.getOrigin()[2])/r.getDirection()[2];
//        tzmax = (min[2]-r.getOrigin()[2])/r.getDirection()[2];
//    }
//
//    if((tmin>tzmax)||(tzmin>tmax)){
//        return false;
//    }
//    if(tzmin > tmin){
//        tmin = tzmin;
//    }
//    if(tzmax < tmax){
//        tmax = tzmax;
//    }
//    return ((tmin < maximum) && (tmax>minimum));
//
//}

//Sphere constructor.
BoundingBox::BoundingBox(float radius, Vector3D center) {
    Vector3D offset(radius,radius,radius);
    min = center - offset;
    max = center + offset;

}

