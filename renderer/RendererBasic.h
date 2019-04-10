//
// Created by brand on 3/26/2019.
//

#ifndef OPENGL_FCG_RENDERERBASIC_H
#define OPENGL_FCG_RENDERERBASIC_H


#include "renderer.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <thread>
#include "framebuffer.h"
#include "PerspectiveCamera.h"

class RendererBasic : public renderer {
public:
    framebuffer fb;
    int rpp;



    RendererBasic(const SceneContainer &sc, int framebufferwidth, int framebufferheight, int rpp);

    void setFb(const framebuffer &fb);

    void paint(const int wMin, const int wMax, const int hMin,const  int hMax) ;

    void test(){

    }

public:

    bool render(std::string output);


};


#endif //OPENGL_FCG_RENDERERBASIC_H
