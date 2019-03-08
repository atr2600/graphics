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


class Light {
private:
    sivelab::Vector3D position, intensity;
public:
    const sivelab::Vector3D &getPosition() const;

    void setPosition(const sivelab::Vector3D &position);

    const sivelab::Vector3D &getIntensity() const;

    void setIntensity(const sivelab::Vector3D &intensity);

    virtual ~Light(){}

    Light(sivelab::Vector3D position, sivelab::Vector3D intensity) : position(position), intensity(intensity){}

    virtual void lightItUp(sivelab::Vector3D &point, sivelab::Vector3D &lightDirction, float &distance) const = 0;

};


#endif //OPENGL_FCG_LIGHT_H
