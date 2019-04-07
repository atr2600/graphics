/**
 * \class Light
 *
 * \ingroup render_util
 *
 * \brief Computer Graphics class.
 *
 * This is the Light class that other shapes will inherent from.
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

#ifndef OPENGL_FCG_LIGHT_H
#define OPENGL_FCG_LIGHT_H

#include "../src/Vector3D.h"


class Light {
protected:
    sivelab::Vector3D position, intensity, normal;
    std::string name;
    float height, width;
public:
    Light(const sivelab::Vector3D &position, const sivelab::Vector3D &intensity, const sivelab::Vector3D &normal,
          float height, float width) : position(position), intensity(intensity), normal(normal), height(height),
                                       width(width) {}

public:

    virtual ~Light(){}

    const sivelab::Vector3D &getPosition() const {
        return position;
    }

    void setPosition(const sivelab::Vector3D &position) {
        Light::position = position;
    }

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        Light::name = name;
    }

    const sivelab::Vector3D &getIntensity() const {
        return intensity;
    }

    void setIntensity(const sivelab::Vector3D &intensity) {
        Light::intensity = intensity;
    }

    const sivelab::Vector3D &getNormal() const {
        return normal;
    }

    void setNormal(const sivelab::Vector3D &normal) {
        Light::normal = normal;
    }

    float getHeight() const {
        return height;
    }

    void setHeight(float height) {
        Light::height = height;
    }

    float getWidth() const {
        return width;
    }

    void setWidth(float width) {
        Light::width = width;
    }

    /**
     * Light Class.
     * @param position
     * @param intensity
     */
    Light(sivelab::Vector3D position, sivelab::Vector3D intensity) : position(position), intensity(intensity){}

    /**
     *  Virtual function that sheds light on the objects.
     * @param point
     * @param lightDirction
     * @param distance
     */
    virtual void lightItUp(sivelab::Vector3D &point, sivelab::Vector3D &lightDirction, float &distance) const = 0;


};


#endif //OPENGL_FCG_LIGHT_H
