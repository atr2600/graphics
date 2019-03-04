//
// Created by brand on 3/4/2019.
//

#ifndef OPENGL_FCG_BOX_H
#define OPENGL_FCG_BOX_H


#include "../src/Vector3D.h"
#include "Triangle.h"

class Box {
private:
    Triangle triangles[12];
    double minPt, maxPt;
public:
    Box(double minPt, double maxPt);


};


#endif //OPENGL_FCG_BOX_H
