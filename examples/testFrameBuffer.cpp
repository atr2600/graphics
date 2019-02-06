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

#include "SceneDataTypes.h"

using namespace sivelab;

int main(int argc, char *argv[])
{
    sive
//    framebuffer test;
    framebuffer test1(4000,4000);
    test1.export_png();

    exit(EXIT_SUCCESS);
}
