//
// Created by brand on 4/29/2019.
//

#ifndef TUTORIALS_RASTERIZE_H
#define TUTORIALS_RASTERIZE_H


#include "renderer.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <thread>
#include "framebuffer.h"
#include "PerspectiveCamera.h"

class rasterize : public renderer{

public:
    rasterize(const SceneContainer &sc, int framebufferwidth, int framebufferheight);
    float baryCords(sivelab::Vector3D v0, sivelab::Vector3D v1, sivelab::Vector3D v2, sivelab::Vector3D P, int option);

    float f20(Vector3D v0, Vector3D v1, int x, int y);

    float f12(Vector3D v0, Vector3D v1,  int x, int y);

    float f01(Vector3D v0, Vector3D v1,  int x, int y);
};


#endif //TUTORIALS_RASTERIZE_H
