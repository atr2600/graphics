/**
 * \class Shape
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

#include "../renderer/HitStruct.h"
#include "../renderer/Ray.h"
#include <string>

class Shape {
private:
    std::string name, color;
    double tvalue;
public:
    double getTvalue() const;

    void setTvalue(double tvalue);

    void setColor(const std::string &color);

    const std::string &getName() const;

    void setName(const std::string &name);

    Shape();

    virtual bool intersect(double tmin, double &tmax, HitStruct &hit, Ray r) = 0;

    const std::string &getColor() const;


};



