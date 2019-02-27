//
// Created by brand on 2/5/2019.
//

#include "Shader.h"
#include "../src/Vector3D.h"

Shader::Shader() {}

Shader::Shader(const sivelab::Vector3D &color) : color(color) {}

const sivelab::Vector3D &Shader::getColor() const {
    return color;
}

void Shader::setColor(const sivelab::Vector3D &color) {
    Shader::color = color;
}

void Shader::setName(const std::string &name) {
    Shader::name = name;
}

const std::string &Shader::getName() const {
    return name;
}
