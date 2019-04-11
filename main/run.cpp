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
#include <chrono>

#include <sys/resource.h>

using namespace sivelab;

inline bool exists_test1 (const std::string& name);



int main(int argc, char *argv[]){

    const rlim_t kStackSize = 32 * 1024 * 1024;

    auto start = std::chrono::steady_clock::now();

    SceneContainer sc;
    GraphicsArgs args;
    args.process(argc, argv);

    std::string path = args.inputFileName;
    if(exists_test1(path)){
        sc.parseJSONData(path);
    }


    RendererBasic rend(sc, args.width,args.height, args.rpp);
    rend.render(args.outputFileName);

    auto end = std::chrono::steady_clock::now();

    std::cout << "Elapsed time in minutes and seconds: " << std::chrono::duration_cast<std::chrono::minutes>(end - start).count() << " min " <<
    (std::chrono::duration_cast<std::chrono::seconds>(end - start).count())%60 << " sec "<<
                                                                               (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count())%1000 << " ms";

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