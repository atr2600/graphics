//
// Created by brand on 3/26/2019.
//

#include "RendererBasic.h"
#include "renderer.h"
#include <cfloat>

RendererBasic::RendererBasic(const SceneContainer &sc, int framebufferwidth, int framebufferheight, int raysPerPixel)
                                                : renderer(sc, framebufferwidth, framebufferheight) {
    setFb(framebuffer(framebufferheight,framebufferwidth));
    setRpp(raysPerPixel);

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
            sivelab::Vector3D background = sivelab::Vector3D(0.5,0.62,0.43);  //r.getDirection();
            sivelab::Vector3D rgb(0,0,0);
            for(int d = 0; d < rpp; d++){
                for(int f= 0; f < rpp; f++){
                    drand48();
                    double softX = drand48();
                    double softY = drand48();
                    Ray r;
                    r = pCam->generateRay(i,j,f,d, rpp); //r.getDirection();
                    double tmax = DBL_MAX;
                    Shape *s = sc.getShapes()[0];
                    sivelab::Vector3D temp = background;
                    for(int z = 0; z< sc.getShapes().size();z++){

                        if(sc.getShapes()[z]->intersect(0.05,tmax,h,r)){
                            if(sc.getShapes()[z]->getTvalue()<tmax){
                                tmax = sc.getShapes()[z]->getTvalue();
                                temp = sc.getShaders().at(sc.getShapes()[z]->getColor())->applyShader(r, sc.getLights(), sc.getShapes(), h, sc.getShaders(),softX,softY);
                            }
                        }

                    }
                    rgb += temp;
                }

            }
            rgb /= (double)(rpp*rpp);
            fb.setPixelColor(rgb, i, j, fb.getWidth());
        }
    }

    fb.export_png(output);

    return true;
}

int RendererBasic::getRpp() const {
    return rpp;
}

void RendererBasic::setRpp(int rpp) {
    RendererBasic::rpp = rpp;
}




