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

#include "SceneDataTypes.h"
#include "../renderer/SceneContainer.h"
#include "../renderer/Sphere.h"
#include "../renderer/HitStruct.h"
#include <limits>
#include <string>

using namespace sivelab;

inline bool exists_test1 (const std::string& name);

int main(int argc, char *argv[]){

framebuffer fb(250, 250);
int temp = fb.getHeight();
SceneContainer sc;
std::string path = "../../renderer/sceneData/scenes_A/oneTriangle.json";

if(exists_test1(path)){
    sc.parseJSONData(path);
}

HitStruct h;
//sc.addShapes(s);
// Create your Perspective Camera using
// focal length  = 1, image plane width = 0.5, position = (0, 0, 0), view direction = (0, 0, -1)
// POSITION - DIRECTION - FOCAL LENGTH - ASPECT RATIO - IMAGE PLANE WIDTH
    //PerspectiveCamera *pCam= new PerspectiveCamera(sivelab::Vector3D(0, 0, 0), sivelab::Vector3D(0, 0, -1), 1, 0.5, 0.5);

    Camera *pCam = sc.getCameras()[0];
    for (int j=0; j<fb.getHeight(); ++j) {
        for (int i=0; i<fb.getWidth(); ++i) {
            Ray r;
            r = pCam->generateRay(i,j);


            Shape *s = sc.getShapes()[0];



            sivelab::Vector3D rgb = r.getDirection();
            rgb[0] += 1;
            rgb[1] += 1;
            rgb[2] += 1;
            rgb /= 2.0;

            if(s->intersect(0.05,DBL_MAX,h,r)){
                rgb[0]=0;
                rgb[1]=0;
                rgb[2]=0;
            }

            fb.setPixelColor(rgb, i, j, fb.getWidth());
        }
    }

    fb.export_png();

}



inline bool exists_test1 (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}