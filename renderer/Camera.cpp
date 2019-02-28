//
// Created by brand on 2/5/2019.
//

#include "Camera.h"

void Camera::setPosition(const sivelab::Vector3D &position) {
    Camera::position = position;
}

void Camera::setDirection(const sivelab::Vector3D &direction) {
    Camera::direction = direction;
}

void Camera::setFocalLength(float focalLength) {
    Camera::focalLength = focalLength;
}

void Camera::setImagePlaneWidth(float imageWidth) {
    Camera::imagePlaneWidth = imageWidth;
}

void Camera::setRatio(float ratio) {
    Camera::ratio = ratio;
}

void Camera::setCsys(const CoordinateSystem &csys) {
    Camera::csys = csys;
}

void Camera::setImagePlaneHeight(float imagePlaneHeight) {
    Camera::imagePlaneHeight = imagePlaneHeight;
}

float Camera::getWidth() const {
    return width;
}

void Camera::setWidth(float width) {
    Camera::width = width;
}

float Camera::getHeight() const {
    return height;
}

void Camera::setHeight(float height) {
    Camera::height = height;
}


