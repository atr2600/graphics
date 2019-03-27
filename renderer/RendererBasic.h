//
// Created by brand on 3/26/2019.
//

#ifndef OPENGL_FCG_RENDERERBASIC_H
#define OPENGL_FCG_RENDERERBASIC_H


#include "renderer.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include "framebuffer.h"

class RendererBasic : public renderer {
private:
    framebuffer fb;
public:
    RendererBasic(const SceneContainer &sc, int framebufferwidth, int framebufferheight);

    void setFb(const framebuffer &fb);

public:

    bool render(std::string output);


};


#endif //OPENGL_FCG_RENDERERBASIC_H
