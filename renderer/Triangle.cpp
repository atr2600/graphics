//
// Created by brand on 2/26/2019.
//


#include <cfloat>
#include "Triangle.h"

Triangle::Triangle() {}

Triangle::Triangle(sivelab::Vector3D v0, sivelab::Vector3D v1, sivelab::Vector3D v2){

//    max = Vector3D(0,0,0);
//    min = Vector3D(0,0,0);

    setV0(v0);
    setV1(v1);
    setV2(v2);


    for(int i = 0; i<3;i++){
        min[i] = (v0[i] < v1[i] ? v0[i]:v1[i]);
        min[i] = (min[i] < v2[i] ? min[i]:v2[i]);

        max[i] = (v0[i] > v1[i] ? v0[i]:v1[i]);
        max[i] = (max[i] > v2[i] ? max[i]:v2[i]);
    }

    
    //Expanding the bounds real quick.
//    min = min - v0;
//    max = max + v0;
//    min = min - v1;
//    max = max + v1;
//    min = min - v2;
//    max = max + v2;

    bounds[0] = min;
    bounds[1] = max;

    mid = (max + min)/2;

}

bool Triangle::intersect(double tmin, double &tmax, HitStruct &hit, Ray r){
using namespace sivelab;
    float t, u, v;
    static const float kEpsilon = 1e-8;
    Vector3D v0v1 = v1 - v0;
    Vector3D v0v2 = v2 - v0;
    Vector3D pvec = r.getDirection().cross(v0v2);
    float det = v0v1.dot(pvec);

    if(fabs(det) < kEpsilon) return false;

    float invDet = 1 /det;

    Vector3D tvec = r.getOrigin() - v0;
    u = tvec.dot(pvec) * invDet;
    if(u<0||u>1)return false;

    Vector3D qvec = tvec.cross(v0v1);
    v = r.getDirection().dot(qvec) * invDet;
    if(v<0||u+v>1) return false;

    t = v0v2.dot(qvec) *invDet;

    sivelab::Vector3D pointOfHit = r.getOrigin() + r.getDirection() *t;

//    tmax = t;
//    if(tmax >)

    if(t>0){
        hit.shader = getColor();
        hit.setActualT(t);
        hit.setPointInterect(pointOfHit);
        hit.setNorm(v0v1.cross(v0v2));
        tvalue = t;


    }

    return (t>0) ? true : false;

}


void Triangle::setV0(const sivelab::Vector3D &v0) {
    Triangle::v0 = v0;
}

void Triangle::setV1(const sivelab::Vector3D &v1) {
    Triangle::v1 = v1;
}

void Triangle::setV2(const sivelab::Vector3D &v2) {
    Triangle::v2 = v2;
}
