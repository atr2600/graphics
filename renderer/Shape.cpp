//
// Created by brand on 2/5/2019.
//

#include "Shape.h"

Shape::Shape() {}

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
