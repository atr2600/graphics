//
// Created by brand on 3/25/2019.
//

#pragma once

#include "../renderer/framebuffer.h"
#include "Ray.h"
#include "SceneContainer.h"
#include "HitStruct.h"

class renderer {
protected:
    SceneContainer sc;
    HitStruct h;
    int framebufferwidth, framebufferheight;
public:
    int getFramebufferwidth() const {
        return framebufferwidth;
    }

    int getFramebufferheight() const {
        return framebufferheight;
    }

    renderer(const SceneContainer &sc, int framebufferwidth, int framebufferheight) : sc(sc), framebufferwidth(
            framebufferwidth), framebufferheight(framebufferheight) {}

    renderer(int framebufferwidth, int framebufferheight) : framebufferwidth(framebufferwidth),
                                                            framebufferheight(framebufferheight) {}


};