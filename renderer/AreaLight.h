//
// Created by khan on 4/6/19.
//

#ifndef OPENGL_FCG_AREALIGHT_H
#define OPENGL_FCG_AREALIGHT_H


#include "Light.h"
#include "CoordinateSystem.h"

class AreaLight : public Light {
private:
    CoordinateSystem lightxyz;
public:
    AreaLight(const sivelab::Vector3D &position, const sivelab::Vector3D &intensity, const CoordinateSystem &lightxyz);

    AreaLight(const sivelab::Vector3D &position, const sivelab::Vector3D &intensity, const sivelab::Vector3D &normal,
              float height, float width);

    const CoordinateSystem &getLightxyz() const;

    void setLightxyz(const CoordinateSystem &lightxyz);

public:


    void lightItUp(sivelab::Vector3D &point, sivelab::Vector3D &lightDirction, float &distance) const;

};


#endif //OPENGL_FCG_AREALIGHT_H
