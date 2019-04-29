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

};


#endif //TUTORIALS_RASTERIZE_H
