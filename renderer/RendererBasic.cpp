//
// Created by brand on 3/26/2019.
//

#include "RendererBasic.h"
#include "renderer.h"
#include <cfloat>

RendererBasic::RendererBasic(const SceneContainer &sc, int framebufferwidth, int framebufferheight)
                                                : renderer(sc, framebufferwidth, framebufferheight) {
    setFb(framebuffer(framebufferheight,framebufferwidth));
}

void RendererBasic::setFb(const framebuffer &fb) {
    RendererBasic::fb = fb;
}

bool RendererBasic::render(std::string output) {
    Camera *pCam = sc.getCameras()[0];
    pCam->setWidth(framebufferwidth);
    pCam->setHeight(framebufferheight);
    for (int j=0; j<fb.getHeight(); ++j) {
        for (int i=0; i<fb.getWidth(); ++i) {
            Ray r;
            r = pCam->generateRay(i,j);
            sivelab::Vector3D rgb = sivelab::Vector3D(0.25,0.23,0.23);  //r.getDirection();
            double tmax = DBL_MAX;
            Shape *s = sc.getShapes()[0];
            for(int i = 0; i< sc.getShapes().size();i++){
                if(sc.getShapes()[i]->intersect(0.05,tmax,h,r)){
                    if(sc.getShapes()[i]->getTvalue()<tmax){
                        tmax = sc.getShapes()[i]->getTvalue();
                        rgb = sc.getShaders().at(sc.getShapes()[i]->getColor())->applyShader(r,sc.getLights(),sc.getShapes(),h, sc.getShaders());
//                        rgb.clamp(0,1);
                    }
                }
            }
            fb.setPixelColor(rgb, i, j, fb.getWidth());
        }
    }

    fb.export_png(output);

    return true;
}




