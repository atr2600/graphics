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
    t = (imageWidth*(height*.5))/width*(-1);
    b = (imageWidth*height*.5)/width;
    r = imageWidth/2;
    l = imageWidth/2*(-1);
//    l = -imageWidth / 2.0 ;
//    r = imageWidth / 2.0;
//    t = imageLength/ 2.0;
//    b = -imageLength / 2.0;


    double u, v, d; //Scalers... d is the distance.(FocalLength)
    d = focalLength;
    u = l + (r-l)*(i+0.5)/(double)width;
    v = b + (t - b)*(j+0.5)/(double)height;


    //origin = e
    //e + -dW + uU + vV is equal to ray direction.

    ray.setOrigin(position);
    dW = (csys.getW());
    vV = (csys.getV()*v);
    uU = (csys.getU()*u);

//    Vector3D *testPTR = new Vector3D(0,0,0);
//    double value = testPTR->normalize();

    newDirection = Vector3D(0,0,0);

    newDirection = (dW * (-1*focalLength))+ uU + vV;
    newDirection.normalize();
    ray.setDirection(newDirection);


    return ray;

}

PerspectiveCamera::PerspectiveCamera() {
    width = 1000;
    height = 1000;
    setRatio(1);
}

PerspectiveCamera::PerspectiveCamera(sivelab::Vector3D position, sivelab::Vector3D direction, double focalLength, double m_aspectRation, double imageWidth){
    width = 1000;
    height = 1000;

    setCsys(CoordinateSystem(direction,sivelab::Vector3D(0,1,0)));
    setRatio(m_aspectRation);
    setDirection(direction);
    setFocalLength(focalLength);
    setImageWidth(imageWidth);
    setImageHeight(imageWidth*m_aspectRation);
    setPosition(position);
}
