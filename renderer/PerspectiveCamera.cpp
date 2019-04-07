//
// Created by brand on 2/5/2019.
//

#include "PerspectiveCamera.h"
#include "../src/Vector3D.h"



/**
 * This generates the rays from the perspective camera.
 * @param i
 * @param j
 * @return
 */
Ray PerspectiveCamera::generateRay(int i, int j, int rppX, int rppY, int rpp) {
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
    u = l + (r-l)*(i+drand48())/(double)width;
    v = b + (t - b)*(j+drand48())/(double)height;

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

/**
 *
 */
PerspectiveCamera::PerspectiveCamera() {
    width = 100;
    height = 100;
    setRatio(1);
}

/**
 * Create that perspective camera class.
 * @param position
 * @param direction
 * @param focalLength
 * @param m_aspectRation
 * @param imagePlaneWidth
 */
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
