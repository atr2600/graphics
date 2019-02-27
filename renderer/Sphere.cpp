//
// Created by brand on 2/5/2019.
//

#include "Sphere.h"
#include <math.h>

Sphere::Sphere() {}

Sphere::Sphere(double c1, double c2, double c3, float newRadius){
    setCenter(sivelab::Vector3D(c1,c2,c3));
    setRadius(newRadius);
}

bool Sphere::intersect(double tmin, double tmax, HitStruct hit, const Ray r) {
    using namespace sivelab;
    float t0,t1;

    double radius2 = pow(radius, 2.0);

    Vector3D L = r.getDirection() - center;
    float a = r.getDirection().dot(r.getDirection());
    float b = 2*r.getDirection().dot(L);
    float c = L.dot(L) - radius2;
    if(!solveQuadratic(a,b,c,t0,t1)) {
        return false;
    }

    if(t0<0||t1<0) return false;

    if (t0<t1){
        tmax = t0;
        hit.setActualT(t0);
    }else {
        tmax = t1;
        hit.setActualT(t1);
    }

    return true;

}

bool Sphere::solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
{
    float discr = b * b - 4 * a * c;
    if (discr < 0) return false;
    else if (discr == 0) x0 = x1 = - 0.5 * b / a;
    else {
        float q = (b > 0) ?
                  -0.5 * (b + sqrt(discr)) :
                  -0.5 * (b - sqrt(discr));
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
