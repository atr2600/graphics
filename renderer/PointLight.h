/**
 * \class PointLight
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

#ifndef OPENGL_FCG_POINTLIGHT_H
#define OPENGL_FCG_POINTLIGHT_H

#include "Light.h"
#include "../src/Vector3D.h"

class PointLight : public Light {
public:


    PointLight(sivelab::Vector3D position, sivelab::Vector3D intensity);

    void lightItUp(sivelab::Vector3D &point, sivelab::Vector3D &lightDirction, float &distance) const ;

};


#endif //OPENGL_FCG_POINTLIGHT_H
