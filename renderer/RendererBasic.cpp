//
// Created by brand on 3/26/2019.
//

#include "RendererBasic.h"
#include "renderer.h"
#include <cfloat>
#include "BVH.h"

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
    BVH boxes(sc.shapes,0);

    for (int j=0; j<fb.getHeight(); ++j) {
        for (int i=0; i<fb.getWidth(); ++i) {
            sivelab::Vector3D background = sivelab::Vector3D(0.5,0.62,0.43);  //r.getDirection();
            sivelab::Vector3D rgb(0,0,0);

//======================================================================================================
//============= UNDER CONSTRUCTION HERE =============== WORKING ON THE BVH =============================
                for(int f= 0; f < rpp; f++){
                    drand48();
                    double softX = drand48();
                    double softY = drand48();
                    Ray r;
                    r = pCam->generateRay(i,j,0,0, rpp); //r.getDirection();
                    double tmax = DBL_MAX;

                    sivelab::Vector3D temp = background;
                  //  for(int z = 0; z< sc.getShapes().size();z++){
                  //this intersect function is always false....
                  Shape *testersphere = boxes.leftChild;

                    if(boxes.intersect(0.006,tmax,h,r)){
                        if(h.getActualT()<9999999){
                            tmax = h.getActualT();
                            temp = sc.getShaders().at(h.shader)->applyShader(r, sc.getLights(), sc.getShapes(), h, sc.getShaders(),softX,softY);
                        }
                    }

                    rgb += temp;
                }

            rgb /= (double)(rpp*rpp);
            fb.setPixelColor(rgb, i, j, fb.getWidth());
// =============================================================================================================
// ============================================================================================================
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




