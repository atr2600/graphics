//
// Created by brand on 2/5/2019.
//

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cassert>

#include "../src/Vector3D.h"
#include "../renderer/framebuffer.h"
#include "../src/XMLSceneParser.h"
#include "../src/handleGraphicsArgs.h"
#include "../renderer/PerspectiveCamera.h"
#include "../renderer/Camera.h"

#include "../renderer/SceneContainer.h"
#include "../renderer/Sphere.h"
#include "../renderer/HitStruct.h"
#include <limits>
#include <string>
#include <../renderer/renderer.h>
#include "../renderer/RendererBasic.h"
#include "../renderer/RendererOpenGL.h"
#include "../renderer/Shader.h"
#include <time.h>
#include "BVH.h"

using namespace sivelab;

inline bool exists_test1 (const std::string& name);



int main(int argc, char *argv[]){

    clock_t tStart = clock();
    SceneContainer sc;
    GraphicsArgs args;
    args.process(argc, argv);

    std::string path = args.inputFileName;
    if(exists_test1(path)){
        sc.parseJSONData(path);
    }


    RendererBasic rend(sc, args.width,args.height, args.rpp);
    rend.render(args.outputFileName);

    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

//
//    RendererOpenGL rend(sc, args.width, args.height);
//    rend.render();

}



inline bool exists_test1 (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}