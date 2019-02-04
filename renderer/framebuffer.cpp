//
// Created by Brandon Geraci on 2/3/19.
//

#include "framebuffer.h"
#include <vector>


/** This is our helper function that sets the pixel color. Pixel by Pixel.
 *
 * @param rgb
 * @param i
 * @param j
 * @param width
 */
void framebuffer::setPixelColor(Vector3D rgb, int i, int j, int width) {
    i = i + width*j;


    this->raster[i].color.b=rgb.color.b;
    this->raster[i].color.g=rgb.color.g;
    this->raster[i].color.r=rgb.color.r;
}

/**
 * This is a constructor that accepts height and width. That way we can create a
 * display that is the correct size.
 *
 *
 * @param height
 * @param width
 */
framebuffer::framebuffer(int height, int width) : height(height), width(width) {
    this->height=height;
    this->width=width;
    Vector3D color = {
            color.color.b=0.0f,
            color.color.g=0.0f,
            color.color.r=0.0f
    };
    for(int i = 0; i< height;i++){
        for (int j=0;j<width;j++){
            setPixelColor(color, i, j, width);
        }
    }
}


/**
 * This will generate a basic framebuffer, size 100x100. It will set the pixel colors to 0.0f.
 */
framebuffer::framebuffer() {
    this->height=100;
    this->width=100;
    Vector3D color = {
            color.color.b=0.0f,
            color.color.g=0.0f,
            color.color.r=0.0f
    };
    for(int i = 0; i< this->height;i++){
        for (int j=0;j<this->width;j++){
            setPixelColor(color, i, j, width);
        }
    }
}

