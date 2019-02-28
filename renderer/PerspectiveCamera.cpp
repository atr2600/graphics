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
    t = (imagePlaneWidth*(height*.5))/width*(-1);
    b = (imagePlaneWidth*height*.5)/width;
    r = imagePlaneWidth/2;
    l = imagePlaneWidth/2*(-1);


    double u, v, d; //Scalers... d is the distance.(FocalLength)
    d = focalLength;
    u = l + (r-l)*(i+0.5)/(double)width;
    v = b + (t - b)*(j+0.5)/(double)height;

    ray.setOrigin(position);
    dW = (csys.getW());
    vV = (csys.getV()*v);
    uU = (csys.getU()*u);
    newDirection = Vector3D(0,0,0);

    newDirection = (dW * (-1*focalLength))+ uU + vV;
    newDirection.normalize();
    ray.setDirection(newDirection);


    return ray;

}

PerspectiveCamera::PerspectiveCamera() {
    width = 100;
    height = 100;
    setRatio(1);
}

PerspectiveCamera::PerspectiveCamera(sivelab::Vector3D position, sivelab::Vector3D direction, double focalLength, double m_aspectRation, double imagePlaneWidth){
    width = 100;
    height = 100;

    setCsys(CoordinateSystem(direction,sivelab::Vector3D(0,1,0)));
    setRatio(m_aspectRation);
    setDirection(direction);
    setFocalLength(focalLength);
    setImagePlaneWidth(imagePlaneWidth);
    setImagePlaneHeight(imagePlaneWidth*m_aspectRation);
    setPosition(position);
}
