//
// Created by brand on 2/5/2019.
//

#include <cfloat>
#include "Shape.h"

Shape::Shape(){

    returnTvalue = DBL_MAX;
    bounds[0] = sivelab::Vector3D(0.0,0.0,0.0);
    bounds[1] = sivelab::Vector3D(0.0,0.0,0.0);
    min = sivelab::Vector3D(0.0,0.0,0.0);
    max = sivelab::Vector3D(0.0,0.0,0.0);

}


void Shape::setName(const std::string &name) {
    Shape::name = name;
}

const std::string &Shape::getName() const {
    return name;
}

void Shape::setColor(const std::string &color) {
    Shape::color = color;
}


const std::string &Shape::getColor() const {
    return color;
}

double Shape::getTvalue() const {
    return tvalue;
}

void Shape::setTvalue(double tvalue) {
    Shape::tvalue = tvalue;
}

const Vector3D &Shape::getMax() const {
    return max;
}

void Shape::setMax(const Vector3D &max) {
    Shape::max = max;
}

const Vector3D &Shape::getMin() const {
    return min;
}

void Shape::setMin(const Vector3D &min) {
    Shape::min = min;
}

const Vector3D &Shape::getXdim() const {
    return xdim;
}

void Shape::setXdim(const Vector3D &xdim) {
    Shape::xdim = xdim;
}

const Vector3D &Shape::getYdim() const {
    return ydim;
}

void Shape::setYdim(const Vector3D &ydim) {
    Shape::ydim = ydim;
}

const Vector3D &Shape::getZdim() const {
    return zdim;
}

void Shape::setZdim(const Vector3D &zdim) {
    Shape::zdim = zdim;
}

bool Shape::compareX(Shape *i, Shape *j) const {
    return (i->getXdim()[1]<j->getXdim()[1]);
}

bool Shape::compareY(Shape *i, Shape *j) const {
    return (i->getYdim()[1]<j->getYdim()[1]);
}

bool Shape::compareZ(Shape *i, Shape *j) const {
    return (i->getZdim()[1]<j->getZdim()[1]);
}

Shape::~Shape() {
}


