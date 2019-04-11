//
// Created by brand on 3/26/2019.
//

#include "RendererBasic.h"
#include "renderer.h"
#include <cfloat>
#include "BVH.h"
#include <math.h>
#include <thread>
#include <iostream>
#include "../main/ThreadPool.h"


RendererBasic::RendererBasic(const SceneContainer &sc, int framebufferwidth, int framebufferheight, int rpp
                             ) : renderer(sc, framebufferwidth, framebufferheight), rpp(rpp), boxes(BVH(sc.shapes,0)) {
    setFb(framebuffer(framebufferheight,framebufferwidth));

}






void RendererBasic::setFb(const framebuffer &fb) {
    RendererBasic::fb = fb;
}

bool RendererBasic::render(std::string output) {
//    ///////////////////////////////////////////////
//    ThreadPool pool(10);
//    pool.init();
//    auto future = pool.submit(&test);
//    future.get();
//    pool.shutdown();
//
//    ///////////////////////////////////////////////


    std::vector<std::thread> v;

    sc.getCameras()[0]->setWidth(framebufferwidth);
    sc.getCameras()[0]->setHeight(framebufferheight);

    //These will be my threads
    int hHeight = floor(fb.getHeight()/2.0);
    int fWidth = floor(fb.getWidth()/2.0);

    int threadCount = 0;

    for (int j=0 ; j<fb.getHeight(); ++j) {
        for (int i=0; i<fb.getWidth(); ++i) {
            v.push_back(std::thread(&RendererBasic::paint, this,i,j,0,0));
            threadCount++;
            if(v.size()==1000){
                threadCount=0;
                for (auto& th : v) th.join();
                v.clear();
            }
        }
    }
    fb.export_png(output);

    return true;
}




void RendererBasic::paint(const int i, const int j, const int hMin, const int hMax) {

            sivelab::Vector3D background = sivelab::Vector3D(0.5,0.62,0.43);  //r.getDirection();
            sivelab::Vector3D rgb(0,0,0);
            HitStruct test;
            for(int f= 0; f < rpp; f++){
                drand48();
                double softX = drand48();
                double softY = drand48();
                Ray r;
                r = sc.getCameras()[0]->generateRay(i,j,0,0, rpp); //r.getDirection();
                double tmax = DBL_MAX;

                sivelab::Vector3D temp = background;

                if(boxes.intersect(0.006,tmax,test,r)){
                    if(test.getActualT()<tmax){
                        tmax = test.getActualT();
                        temp = sc.getShaders().at(test.shader)->applyShader(r, sc.getLights(), test, sc.getShaders(),softX,softY, boxes);
                    }
                }
                rgb += temp;
            }
            rgb /= (double)(rpp);
            fb.setPixelColor(rgb, i, j, fb.getWidth());

}















