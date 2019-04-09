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

using namespace sivelab;

class Shape {
public:
    Vector3D bounds[2];
    Shape * leftChild;
    Shape * rightChild;
    std::string name, color, returnName;
    double returnTvalue;
    bool isthisabox;
    Vector3D max;
    Vector3D min;
    Vector3D mid;
    sivelab::Vector3D xdim, ydim, zdim;
public:
    const Shape &getReturnShape() const;

    Shape();

    const Vector3D &getXdim() const;

    void setXdim(const Vector3D &xdim);

    const Vector3D &getYdim() const;

    void setYdim(const Vector3D &ydim);

    const Vector3D &getZdim() const;

    void setZdim(const Vector3D &zdim);

    const Vector3D &getMax() const;

    void setMax(const Vector3D &max);

    const Vector3D &getMin() const;

    void setMin(const Vector3D &min);

    bool compareX(Shape *i, Shape *j) const;

    bool compareY(Shape *i, Shape *j) const;

    bool compareZ(Shape *i, Shape *j) const;

public:

protected:
    double tvalue;
public:
    double getTvalue() const;

    void setTvalue(double tvalue);

    void setColor(const std::string &color);

    const std::string &getName() const;

    void setName(const std::string &name);

    virtual bool intersect(double tmin, double &tmax, HitStruct &hit, Ray r) = 0;

    const std::string &getColor() const;


};



