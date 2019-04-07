//
// Created by khan on 4/7/19.
//

#ifndef OPENGL_FCG_BOUNDINGBOX_H
#define OPENGL_FCG_BOUNDINGBOX_H


#include "../src/Vector3D.h"
#include "HitStruct.h"
#include "Ray.h"

using namespace sivelab;

class BoundingBox {

public:

    ////////////////////////////////////////////////////////

    /**
     *
     */
    BoundingBox();

    BoundingBox(float radius, Vector3D center);

    /**
     *
     * @param min
     * @param max
     */
    BoundingBox(const Vector3D &min, const Vector3D &max);

    //////////////// VARIABLES ////////////////////////////////

    /**
     *
     *
     */
    Vector3D min, max;

//    bool intersect(double minimum, double &maximum, HitStruct &hit, Ray r,Shape * s);

    ////////////// FUNCTIONS /////////////////////////////////////

    /**
     *
     * @param pnt
     */
    void expand(Vector3D pnt);

    /**
     *
     * @param value
     */
    void expandValue(double value);

    /**
     *
     * @return
     */
    Vector3D centerPoint() const;



};


#endif //OPENGL_FCG_BOUNDINGBOX_H
