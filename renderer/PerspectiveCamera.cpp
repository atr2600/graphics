//
// Created by brand on 2/5/2019.
//

#include "PerspectiveCamera.h"
#include "../src/Vector3D.h"




Ray PerspectiveCamera::generateRay(int i, int j) {
    Ray ray;
    using namespace sivelab;
    /**
     * origin + (-distance(W vector)+uU + vV)
     */


    Vector3D uU, vV, dW, newDirection; //Vectors
    double t, b, r, l; //TOP BOTTOM RIGHT LEFT
//    t = (imageWidth*height)/width*(-1);
//    b = (imageWidth*height)/width;
//    r = imageWidth/2;
//    l = imageWidth/2*(-1);
    l = -imageWidth / 2.0 ;
    r = imageWidth / 2.0;
    t = imageLength/ 2.0;
    b = -imageLength / 2.0;


    double u, v, d; //Scalers... d is the distance.(FocalLength)
    d = focalLength;
    u = l + (r-l)*(i+0.5)/(double)width;
    v = b + (t - b)*(j+0.5)/(double)height;

    //origin = e
    //e + -dW + uU + vV is equal to ray direction.

    ray.setOrigin(position);
    dW = csys.getW();
    vV = csys.getV();
    uU = csys.getU();

    uU *= u;
    vV *= v;

    newDirection = Vector3D(0,0,0);
    newDirection += dW;
    newDirection *= (-1*focalLength); //try that?
    newDirection += uU; //this looks fine
    newDirection += vV; //this looks fine
    ray.setDirection(newDirection);

    return ray;

}

PerspectiveCamera::PerspectiveCamera() {
    width = 350;
    height = 250;
    setRatio(1);
}

PerspectiveCamera::PerspectiveCamera(double focalLength, double imageWidth, sivelab::Vector3D position, sivelab::Vector3D direction){
    width = 350;
    height = 250;
    setCsys(CoordinateSystem(direction,sivelab::Vector3D(0,1,0)));
    setRatio(1);
    setDirection(direction);
    setFocalLength(focalLength);
    setImageWidth(imageWidth);
    setPosition(position);
}
