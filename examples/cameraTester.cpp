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

using namespace sivelab;

int main(int argc, char *argv[]){

framebuffer fb(250,350);
int temp = fb.getHeight();

// Create your Perspective Camera using
// focal length  = 1, image plane width = 0.5, position = (0, 0, 0), view direction = (0, 0, -1)
    PerspectiveCamera *pCam= new PerspectiveCamera(1.0f, 0.5f, sivelab::Vector3D(0, 0, 0), sivelab::Vector3D(1, 0, 0));
    for (int j=0; j<fb.getHeight(); ++j) {
        for (int i=0; i<fb.getWidth(); ++i) {
            Ray r;
            r = pCam->generateRay(i,j);


            sivelab::Vector3D rgb = r.getDirection();
            rgb[0] += 1;
            rgb[1] += 1;
            rgb[2] += 1;
            rgb /= 2.0;
            fb.setPixelColor(rgb, i, j, fb.getWidth());
        }
    }

    fb.export_png();

}
