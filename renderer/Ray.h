//
// Created by brand on 2/12/2019.
//

#ifndef OPENGL_FCG_RAY_H
#define OPENGL_FCG_RAY_H

#include"../src/Vector3D.h"

class Ray {
private:
    sivelab::Vector3D direction;
public:
    const sivelab::Vector3D &getDirection() const;

    const sivelab::Vector3D &getOrigin() const;

private:
    sivelab::Vector3D origin;



public:
    void setDirection(const sivelab::Vector3D &direction);
    void setOrigin(const sivelab::Vector3D &origin);

    Ray();
    Ray(const sivelab::Vector3D &dir, const sivelab::Vector3D &orig);

};


#endif //OPENGL_FCG_RAY_H
