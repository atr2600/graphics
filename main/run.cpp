//
// Created by brand on 2/5/2019.
//

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cassert>

#include "Vector3D.h"
#include "../renderer/framebuffer.h"
#include "XMLSceneParser.h"
#include "handleGraphicsArgs.h"
#include "../renderer/PerspectiveCamera.h"
#include "../renderer/Camera.h"

#include "../renderer/SceneContainer.h"
#include "../renderer/Sphere.h"
#include "../renderer/HitStruct.h"
#include <limits>
#include <string>
#include "../renderer/Shader.h"

using namespace sivelab;

inline bool exists_test1 (const std::string& name);

int main(int argc, char *argv[]){

    GraphicsArgs args;
    args.process(argc, argv);
    framebuffer fb(args.width, args.height);
    int temp = fb.getHeight();
    SceneContainer sc;
    std::string path = args.inputFileName;
    if(exists_test1(path)){
        sc.parseJSONData(path);
    }

    //std::map<std::string, Shader *> colors = sc.getShaders();

    HitStruct h;
    // focal length  = 1, image plane width = 0.5, position = (0, 0, 0), view direction = (0, 0, -1)
    // POSITION - DIRECTION - FOCAL LENGTH - ASPECT RATIO - IMAGE PLANE WIDTH
    //PerspectiveCamera *pCam= new PerspectiveCamera(sivelab::Vector3D(0, 0, 0), sivelab::Vector3D(0, 0, -1), 1, 0.5, 0.5);

    Camera *pCam = sc.getCameras()[0];
    pCam->setWidth(args.width);
    pCam->setHeight(args.height);
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
                        //rgb = sc.getShaders().at(sc.getShapes()[i]->getColor())->getColor();
                        rgb = sc.getShaders().at(sc.getShapes()[i]->getColor())->applyShader(r,sc.getLights(),sc.getShapes(),h);
                    }
                }
            }
            fb.setPixelColor(rgb, i, j, fb.getWidth());
        }
    }

    fb.export_png(args.outputFileName);

}



inline bool exists_test1 (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}