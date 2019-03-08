//
// Created by brand on 2/5/2019.
//

#include "Sphere.h"
#include <math.h>


/**
 *
 */
Sphere::Sphere() {}

/**
 *
 * @param c1
 * @param c2
 * @param c3
 * @param newRadius
 */
Sphere::Sphere(double c1, double c2, double c3, float newRadius){
    setCenter(sivelab::Vector3D(c1,c2,c3));
    setRadius(newRadius);
}

/**
 *
 * @param tmin
 * @param tmax
 * @param hit
 * @param r
 * @return
 */
bool Sphere::intersect(double tmin, double tmax, HitStruct hit, const Ray r) {
    using namespace sivelab;
    float t0,t1;

    Vector3D L = r.getOrigin() - center;
    float a = r.getDirection().dot(r.getDirection());
    float b = 2 * r.getDirection().dot(L);
    float c = L.dot(L)-(radius*radius);
    if(!solveQuadratic(a,b,c,t0,t1))return false;

    if (t0>t1) std::swap(t0,t1);

    if(t0<0){
        t0 = t1;
        if(t0<0) return false;
    }

    tmax = t0;
    hit.setActualT(t0);
    setTvalue(t0);
    return true;


}

/**
 *
 * @param a The A value in the quadratic formula.
 * @param b The B value in the quadratic formula.
 * @param c The C value in the quadratic formula.
 * @param x0
 * @param x1
 * @return
 */
bool Sphere::solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
{
    float discr = b * b - 4 * a * c;
    if (discr < 0) return false;
    else if (discr == 0) x0 = x1 = - 0.5 * b / a;
    else {
        float q;
        if (b > 0) {
            q = -0.5 * (b + sqrt(discr));
        } else {
            q = -0.5 * (b - sqrt(discr));
        }
        x0 = q / a;
        x1 = c / q;
    }
    if (x0 > x1) std::swap(x0, x1);

    return true;
}

void Sphere::setCenter(const sivelab::Vector3D &center) {
    Sphere::center = center;
}

void Sphere::setRadius(float radius) {
    Sphere::radius = radius;
}
