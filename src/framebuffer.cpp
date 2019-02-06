//
// Created by Brandon Geraci on 2/3/19.
//
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "framebuffer.h"
#include <vector>
#include "Vector3D.h"
#include "png++/png.hpp"

void framebuffer::export_png(std::vector<sivelab::Vector3D> data, int w, int h) {
    png::image<png::rgb_pixel > imData(w,h);

    for (size_t y = 0; y < imData.get_height(); ++y)
    {
        for (size_t x = 0; x < imData.get_width(); ++x)
        {
            int i = x + w*y;
            sivelab::Vector3D temp =  data.at(i);
            imData[y][x] = png::rgb_pixel(temp[0], temp[1], temp[3]);
        }
    }

    imData.write("blah.png");
}

/** This is our helper function that sets the pixel color. Pixel by Pixel.
 *
 * @param rgb
 * @param i
 * @param j
 * @param width
 */
void framebuffer::setPixelColor(sivelab::Vector3D rgb, int i, int j, int width) {
    int loc;
    loc = i + width * j;

    this->data[loc] = rgb;


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
    int size = height*width;
    std::vector<sivelab::Vector3D> data(size);

    for(int i = 0; i< height;i++){
        for (int j=0;j<width;j++){
            sivelab::Vector3D c( 0.0f, 0.0f, 0.0f );
            setPixelColor(c, i, j, width);
        }
    }
}


/**
 * This will generate a basic framebuffer, size 100x100. It will set the pixel colors to 0.0f.
 */
framebuffer::framebuffer() {
    this->height=100;
    this->width=100;
    std::vector<sivelab::Vector3D> data(1000);


    for(int i = 0; i< this->height;i++){
        for (int j=0;j<this->width;j++){
            sivelab::Vector3D c( 0.0f, 0.0f, 0.0f );
            setPixelColor(c, i, j, width);
        }
    }
}



