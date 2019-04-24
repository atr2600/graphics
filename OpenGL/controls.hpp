#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include <glm/mat4x4.hpp>

void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif