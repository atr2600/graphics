//
// Created by brand on 2/5/2019.
//

#include "PerspectiveCamera.h"
#include "../src/Vector3D.h"




Ray PerspectiveCamera::generateRay(int i, int j) {
    Ray r;
//    r.setOrigin(position);
//    r.setDirection((focalLength * csys.getW() + csys.getU() * csys.getV()));
//    r.origin = position;
//    r.direction = focalLength * csys.getW() + csys.getU() * csys.getV();

    float imageHeight = imageWidth*(1/ratio);

    double left = (-imageWidth/2);
    double right = (imageWidth/2);
    double bottom = (-imageWidth/2);
    double top = imageHeight/2;

    double u = left+(right -left)*(j+0.5)/width;
    double v = bottom + ( top - bottom) * (i+0.5) / height;

    sivelab::Vector3D uU = u * csys.getU();
    sivelab::Vector3D vV = v * csys.getV();



    r.setOrigin(csys.getW()*(-1)*focalLength+uU+vV);
    r.setDirection(position);


    return r;

}

PerspectiveCamera::PerspectiveCamera() {
    setRatio(1);
}

PerspectiveCamera::PerspectiveCamera(float focalLength, float imageWidth, sivelab::Vector3D position, sivelab::Vector3D direction){
    setRatio(1);
    setDirection(direction);
    setFocalLength(focalLength);
    setImageWidth(imageWidth);
    setPosition(position);
}
