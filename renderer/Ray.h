//
// Created by brand on 2/12/2019.
//

#ifndef OPENGL_FCG_RAY_H
#define OPENGL_FCG_RAY_H


class Ray {
private:
    sivelab::Vector3D direction;
public:
    void setDirection(const sivelab::Vector3D &direction);

    void setOrigin(const sivelab::Vector3D &origin);

private:
    sivelab::Vector3D origin;
public:


};


#endif //OPENGL_FCG_RAY_H
