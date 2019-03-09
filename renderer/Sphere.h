/**
 * \class Sphere
 *
 * \ingroup render_util
 *
 * \brief Computer Graphics class.
 *
 *
 *
 * \note University of Minnesota Duluth Computer Graphics
 *
 * \author (last to touch it) $Author: bv Brandon Geraci$
 *
 * \version $Revision: 0.0 $
 *
 * \date $Date: 2019/02/06 8:16:20 $
 *
 * Contact: bran0847@d.umn.edu
 *
 * Created on: Wed Feb 6 18:39:37 2019
 *
 */

#pragma once
#include "../renderer/Shape.h"

class Sphere: public Shape {
private:
    sivelab::Vector3D center = sivelab::Vector3D(0,0.0,-5);
public:
    void setCenter(const sivelab::Vector3D &center);

    void setRadius(float radius);

private:
    float radius = 1.0;

public:
    Sphere();
    Sphere(double c1, double c2, double c3, float newRadius);
    bool intersect(double tmin, double tmax, HitStruct &hit, const Ray r);
    bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1);

};


