//
// Created by brand on 3/4/2019.
//

#include <cfloat>
#include "Box.h"

/**
 * Creates a box object.
 * @param minPt
 * @param maxPt
 */
Box::Box(sivelab::Vector3D minPt, sivelab::Vector3D maxPt) : minPt(minPt), maxPt(maxPt) {
    pts[0] = minPt;
    pts[1] = maxPt;
    pts[2] = sivelab::Vector3D(pts[0][0], pts[0][1], pts[1][2]);
    pts[3] = sivelab::Vector3D(pts[0][0], pts[1][1], pts[0][2]);
    pts[4] = sivelab::Vector3D(pts[1][0], pts[0][1], pts[0][2]);
    pts[5] = sivelab::Vector3D(pts[0][0], pts[1][1], pts[1][2]);
    pts[6] = sivelab::Vector3D(pts[1][0], pts[0][1], pts[1][2]);
    pts[7] = sivelab::Vector3D(pts[1][0], pts[1][1], pts[0][2]);

    //top of box (6,2,8,4)
    triangles[0] = Triangle(pts[5],pts[1],pts[7]);
    triangles[1] = Triangle(pts[5],pts[3],pts[7]);
    //bottom of box (3,7,5,1)
    triangles[2] = Triangle(pts[2],pts[6],pts[4]);
    triangles[3] = Triangle(pts[2],pts[0],pts[4]);
    //front
    triangles[4] = Triangle(pts[3],pts[7],pts[4]);
    triangles[5] = Triangle(pts[3],pts[0],pts[4]);
    //Back
    triangles[6] = Triangle(pts[5],pts[2],pts[6]);
    triangles[7] = Triangle(pts[5],pts[1],pts[6]);
    // left side
    triangles[8] = Triangle(pts[5],pts[2],pts[0]);
    triangles[9] = Triangle(pts[5],pts[3],pts[0]);
    // right side
    triangles[10] = Triangle(pts[1],pts[6],pts[4]);
    triangles[11] = Triangle(pts[1],pts[7],pts[4]);
}

/**
 * Intersect function for the box object.
 * @param tmin
 * @param tmax
 * @param hit
 * @param r
 * @return
 */
bool Box::intersect(double tmin, double &tmax, HitStruct &hit, Ray r){

    bool test = false;
    for(int i = 0;i<12;i++){
        if(triangles[i].intersect(0.0001,tmax, hit, r)){
            tmax = hit.getActualT();
            test = true;
        }
    }
    return test;

}