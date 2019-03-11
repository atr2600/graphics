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
    using namespace sivelab;
    pts[0] = minPt;
    pts[1] = maxPt;
    pts[2] = sivelab::Vector3D(pts[0][0], pts[0][1], pts[1][2]);  //min, min, max
    pts[3] = sivelab::Vector3D(pts[0][0], pts[1][1], pts[0][2]);  //min max min
    pts[4] = sivelab::Vector3D(pts[1][0], pts[0][1], pts[0][2]);  //max, min, min
    pts[5] = sivelab::Vector3D(pts[0][0], pts[1][1], pts[1][2]);  //min, max, max
    pts[6] = sivelab::Vector3D(pts[1][0], pts[0][1], pts[1][2]);  //max, min, max
    pts[7] = sivelab::Vector3D(pts[1][0], pts[1][1], pts[0][2]);  //max, max, min


//
//    //top of box (6,2,8,4)
    triangles[0] = Triangle(pts[7],pts[5],pts[1]);
    triangles[1] = Triangle(pts[7],pts[3],pts[5]);
    //bottom of box (3,7,5,1)
    triangles[2] = Triangle(pts[2],pts[6],pts[4]);
    triangles[3] = Triangle(pts[2],pts[4],pts[0]);
//    //front
    triangles[4] = Triangle(pts[4],pts[7],pts[3]);
    triangles[5] = Triangle(pts[4],pts[3],pts[0]);
 //   Back
    triangles[6] = Triangle(pts[5],pts[2],pts[6]);
    triangles[7] = Triangle(pts[5],pts[6],pts[1]);
//    // left side
    triangles[8] = Triangle(pts[5],pts[2],pts[0]);
    triangles[9] = Triangle(pts[5],pts[0],pts[3]);
//    // right side
    triangles[10] = Triangle(pts[1],pts[4],pts[6]);
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

//I do not store boxes in the stack. I only store the 12 triangles when you parse a box.

}

Triangle *Box::getTriangles(){
    return triangles;
}
