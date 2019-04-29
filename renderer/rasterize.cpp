//
// Created by brand on 4/29/2019.
//

#include "rasterize.h"
#include "renderer.h"
#include <cfloat>
#include "BVH.h"
#include <math.h>
#include <thread>
#include <iostream>
#include "../main/ThreadPool.h"
#include "Triangle.h"

typedef struct tri {
//        float sx[3];
//        float sy[3];
//        float nx[3];
//        float ny[3];
//        float b[3];
    sivelab::Vector3D sx,sy,nx,ny,b;
    int xmin;
    int xmax;
    int ymin;
    int ymax;
} tri;

rasterize::rasterize(const SceneContainer &sc, int framebufferwidth, int framebufferheight) : renderer(sc,
                                                                                                       framebufferwidth,
                                                                                                       framebufferheight) {
    framebuffer fb(framebufferheight, framebufferwidth);
    auto triangleList = sc.shapes;
    Shape *sPtr = nullptr;
    tri tr;
    int width = framebufferwidth;
    int height = framebufferheight;
    HitStruct test;
    float d1, d2, d3, r,g,b;
    int x,y;
    float z;
    float l;

    float* zbuf = (float*)malloc( sizeof(float) * width * height );
    for( int y = 0; y < height; y++ ) {
        for( int x = 0; x < width; x++ ) {
            zbuf[y*width+x] = FLT_MIN;
        }
    }


    for(int i = 0; i < 3;i++){

        sPtr = sc.shapes[i];

        if((sPtr->ydim[0] - sPtr->xdim[0]) *
           (sPtr->zdim[1] - sPtr->xdim[1]) -
           (sPtr->zdim[0] - sPtr->xdim[0]) *
           (sPtr->ydim[1] - sPtr->xdim[1])
           < 0)
        {
            continue;
        }

        tr.sx[0] = (((sPtr->xdim[0])+1)*((float)(framebufferwidth/2)));
        tr.sy[0] = (((sPtr->ydim[1])+1+1)*((float)(framebufferheight/2)));
        tr.sx[1] = (((sPtr->xdim[0])+1)*((float)(framebufferwidth/2)));
        tr.sy[1] = (((sPtr->ydim[1])+1+1)*((float)(framebufferheight/2)));
        tr.sx[2] = (((sPtr->xdim[0])+1)*((float)(framebufferwidth/2)));
        tr.sy[2] = (((sPtr->ydim[1])+1+1)*((float)(framebufferheight/2)));

        // Normals
        for( i = 0; i < 3; i++ )
            //CHECK HERE FOR BAD
            tr.nx[i] = -(tr.sy[(i+1)%3] - tr.sy[i]);
            tr.ny[i] =  (tr.sx[(i+1)%3] - tr.sx[i]);
            l = sqrt( tr.nx[i] * tr.nx[i] + tr.ny[i] * tr.ny[i] );
            tr.nx[i] /= l;
            tr.ny[i] /= l;
        }

        // For barycentric coordinates
        for( i = 0; i < 3; i++ ) {
            tr.b[i] = tr.nx[i] * ( tr.sx[(i+2)%3] - tr.sx[i] ) + tr.ny[i] * ( tr.sy[(i+2)%3] - tr.sy[i] );
        }

        // Bounding rectangles.
        tr.xmin = floor( fmin( fmin( tr.sx[0], tr.sx[1] ), tr.sx[2] ) );
        tr.ymin = floor( fmin( fmin( tr.sy[0], tr.sy[1] ), tr.sy[2] ) );
        tr.xmax = ceil( fmax( fmax( tr.sx[0], tr.sx[1] ), tr.sx[2] ) );
        tr.ymax = ceil( fmax( fmax( tr.sy[0], tr.sy[1] ), tr.sy[2] ) );
        // Clip and possibly rejectr.
        tr.xmin = fmax(0, tr.xmin);
        tr.xmax = fmin(framebufferwidth, tr.xmax);
        tr.ymin = fmax(0, tr.ymin);
        tr.ymax = fmin(framebufferheight, tr.ymax);
        if(tr.ymin > tr.ymax || tr.xmin > tr.xmax) {
            continue;
        }

        for( y = 0; y < height; y++ ) {
            for( x = 0; x < width; x++ ) {
                sivelab::Vector3D temp = sivelab::Vector3D(0.5,0.62,0.43);
                fb.setPixelColor(temp, x, y, fb.getWidth());
                d1 = tr.nx[0] * ( x - tr.sx[0] ) + tr.ny[0] * ( y - tr.sy[0] );
                if( d1 >= 0 ) {
                    if( d1 >= 0 ) {
                        d2 = tr.nx[1] * ( x - tr.sx[1] ) + tr.ny[1] * ( y - tr.sy[1] );
                        if( d2 >= 0 ) {
                            d3 = tr.nx[2] * ( x - tr.sx[2] ) + tr.ny[2] * ( y - tr.sy[2] );
                            if( d3 >= 0 ) {
                                d1 /= tr.b[0];
                                d2 /= tr.b[1];
                                d3 /= tr.b[2];

                                // Z test
                                z =
                                        1.0f / sPtr->xdim[2] * d2 +
                                        1.0f / sPtr->ydim[2] * d3 +
                                        1.0f / sPtr->zdim[2] * d1;

                                if( z > zbuf[y*width+x] ) {
                                    zbuf[y*width+x] = z;
                                    temp = sc.shaderMap.at(sPtr->getColor())->color;
                                    fb.setPixelColor(temp, x, y, fb.getWidth());
//                                r =
//                                        sPtr->colors[0][0] * d2 +
//                                        sPtr->colors[1][0] * d3 +
//                                        sPtr->colors[2][0] * d1;
//                                g =
//                                        sPtr->colors[0][1] * d2  +
//                                        sPtr->colors[1][1] * d3  +
//                                        sPtr->colors[2][1] * d1;
//                                b =
//                                        sPtr->colors[0][2] * d2 +
//                                        sPtr->colors[1][2] * d3 +
//                                        sPtr->colors[2][2] * d1;


//                                setPixel(*pbuf, x, y, makeColour(r,g,b));
                                }
                            }
                        }
                    }
                }
            }

        }


    }
    fb.export_png("../../test.png");
}
