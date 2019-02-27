//
// Created by Brandon Geraci on 2/3/19.
//
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "framebuffer.h"
#include "../src/handleGraphicsArgs.h"


void framebuffer::export_png() {
    sivelab::Random prng;
    png::image<png::rgb_pixel > imData(width,height);

    for (size_t y = 0; y < imData.get_height(); ++y)
    {
        for (size_t x = 0; x < imData.get_width(); ++x)
        {
            int i = x + width*y;
            sivelab::Vector3D color =  data[i];

//            for (int i = 0; i < imgArray.length / 2; i++) {
//                for (int j = 0; j < imgArray[i].length; j++) {
//                    temp = imgArray[i][j];
//                    imgArray[i][j] = imgArray[imgArray.length - 1 - i][j];
//                    imgArray[imgArray.length - 1 -i][j] = temp;
//                }
//            }

//            imData[imData.get_height() - 1 - y][x] = png::rgb_pixel(fmin(color[0], 1) * 255,
//                                                  fmin(color[1], 1) * 255,
//                                                  fmin(color[2], 1) * 255);
            imData[imData.get_height() - 1 - y][x] = png::rgb_pixel(fmin(color[0], 1) * 255,
                                                                    fmin(color[1], 1) * 255,
                                                                    fmin(color[2], 1) * 255);

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

    data[loc]=rgb;
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
    data.resize(width * height);

    for(int i = 0; i< height;i++){
        for (int j=0;j<width;j++){
            sivelab::Vector3D c( 0.0f, 0.0f, 0.0f );
            setPixelColor(c, j, i, width);
        }
    }
}


//This is a test method. Might not work out so well.
framebuffer::framebuffer(int argc, char **argv) {
    sivelab::GraphicsArgs args;
    args.process(argc,argv);

    height = args.height;
    width = args.width;
    data.resize(width * height);

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
    data.resize(width * height);


    for(int i = 0; i< this->height;i++){
        for (int j=0;j<this->width;j++){
            sivelab::Vector3D c( 0.0f, 0.0f, 0.0f );
            setPixelColor(c, i, j, width);
        }
    }
}

int framebuffer::getHeight() const {
    return height;
}

int framebuffer::getWidth() const {
    return width;
}



