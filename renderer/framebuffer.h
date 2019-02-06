//
// Created by Brandon Geraci on 2/3/19.
//

#pragma once


/**
 * The memory allocated for the two-dimensions of the Framebuffer should all be kept in a linear memory structure while supporting array access through two dimensions.
 *
 * Framebuffers will store pixel data at each (i, j) array index in the form of a floating-point Red, Green, and Blue component.
 *
 * Constructors should specify the dimensions (and default dimensions) while also setting all initial values for the pixels to (0.0f, 0.0f, 0.0f).
 *
 * Force pixels to be set through a public member function: setPixel.
 *
 * Allow the Framebuffer array contents to be output to a PNG file through a public function: exportAsPNG, which takes a string as input indicating the filename.
 */

#include <vector>
#include"../src/Vector3D.h"
#include "../src/png++/png.hpp"
#include "../src/Random.h"


/**
 * This is our frame buffer class.
 *
 * This class has height and width to determine the display size. It also contains a raster variable.
 * The raster variable is a vector of Vector3D objects.
 */
class framebuffer {
private:
    /**
     * Support for any dimension in X and Y (within reason -- obviously instancing a Framebuffer that requires more memory than is on your machine is a different requirement).
     */
    int height;
    int width;

    /**
     * Creating the raster
     */
    std::vector<sivelab::Vector3D> data;

public:
    /**
     * Constructors
     */
    framebuffer();

    framebuffer(int height, int width);

    framebuffer(int argc, char *argv[]);


    /**
     * Helper Function setPixelColor. This will take in a rgb object along with the location and the width of the screen.
     * @param rgb
     * @param i
     * @param j
     * @param width
     */
    void setPixelColor(sivelab::Vector3D rgb, int i, int j, int width);

    void export_png();

};




