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

//model globalModel;

#define SCREEN_X(p) (((p)+1)*((float)(width/2)))
#define SCREEN_Y(p) (((p)+1)*((float)(height/2)))

typedef struct tri {
    float sx[3];
    float sy[3];
    float nx[3];
    float ny[3];
    float b[3];
    int xmin;
    int xmax;
    int ymin;
    int ymax;
} tri;

rasterize::rasterize(const SceneContainer &sc, int framebufferwidth, int framebufferheight) : renderer(sc,
                                                                                                       framebufferwidth,
                                                                                                       framebufferheight) {
    float* zbuf = (float*)malloc( sizeof(float) * framebufferwidth * framebufferheight );
    for(int y = 0; y < framebufferheight; y++ ) {
        for(int x = 0; x < framebufferwidth; x++ ) {
            zbuf[y*framebufferwidth+x] = -33;
        }
    }

    int width = framebufferwidth;
    int height = framebufferheight;
    framebuffer fb = framebuffer(height,width);

    // Status variables.
    tri t;
    Shape* modelTri;
    float d1;
    float d2;
    float d3;
    float r;
    float g;
    float b;
    sivelab::Vector3D newcolor;
    float z;
    float l;

    // The actual rasterizer.
    for(int index = 0; index < sc.shapes.size(); index++) {
        modelTri = sc.shapes[index];
        
        if( 
                (modelTri->v1[0] - modelTri->v0[0]) *
                (modelTri->v2[1] - modelTri->v0[1]) -
                (modelTri->v2[0] - modelTri->v0[0]) *
                (modelTri->v1[1] - modelTri->v0[1])
                < 0
                ) {
            continue;
        }

        t.sx[0] = SCREEN_X( modelTri->v0[0] );
        t.sy[0] = SCREEN_Y( modelTri->v0[1] );
        t.sx[1] = SCREEN_X( modelTri->v1[0] );
        t.sy[1] = SCREEN_Y( modelTri->v1[1] );
        t.sx[2] = SCREEN_X( modelTri->v2[0] );
        t.sy[2] = SCREEN_Y( modelTri->v2[1] );

        // Normals
        for( int i = 0; i < 3; i++ ) {
            t.nx[i] = -(t.sy[(i+1)%3] - t.sy[i]);
            t.ny[i] =  (t.sx[(i+1)%3] - t.sx[i]);
            l = sqrt( t.nx[i] * t.nx[i] + t.ny[i] * t.ny[i] );
            t.nx[i] /= l;
            t.ny[i] /= l;
        }

        // For barycentric coordinates
        for(int i = 0; i < 3; i++ ) {
            t.b[i] = t.nx[i] * ( t.sx[(i+2)%3] - t.sx[i] ) + t.ny[i] * ( t.sy[(i+2)%3] - t.sy[i] );
        }

        // Bounding rectangles.
        t.xmin = floor( fmin( fmin( t.sx[0], t.sx[1] ), t.sx[2] ) );
        t.ymin = floor( fmin( fmin( t.sy[0], t.sy[1] ), t.sy[2] ) );
        t.xmax = ceil( fmax( fmax( t.sx[0], t.sx[1] ), t.sx[2] ) );
        t.ymax = ceil( fmax( fmax( t.sy[0], t.sy[1] ), t.sy[2] ) );

        // Clip and possibly reject.
        t.xmin = fmax(0, t.xmin);
        t.xmax = fmin(width, t.xmax);
        t.ymin = fmax(0, t.ymin);
        t.ymax = fmin(height, t.ymax);

//        if(t.ymin > t.ymax || t.xmin > t.xmax) {
//            continue;
//        }
        // Draw pixels inside, if need be
        for( int y = t.ymin; y < t.ymax; y++ ) {
            for( int x = t.xmin; x < t.xmax; x++ ) {
                d1 = t.nx[0] * ( x - t.sx[0] ) + t.ny[0] * ( y - t.sy[0] );
                if( d1 >= 0 ) {
                    d2 = t.nx[1] * ( x - t.sx[1] ) + t.ny[1] * ( y - t.sy[1] );
                    if( d2 >= 0 ) {
                        d3 = t.nx[2] * ( x - t.sx[2] ) + t.ny[2] * ( y - t.sy[2] );
                        if( d3 >= 0 ) {
                            d1 /= t.b[0];
                            d2 /= t.b[1];
                            d3 /= t.b[2];

                            // Z test
                            z =
                                    1.0f / modelTri->v0[2] * d2 +
                                    1.0f / modelTri->v1[2] * d3 +
                                    1.0f / modelTri->v2[2] * d1;

                            if( z > zbuf[y*width+x] ) {
                                zbuf[y*width+x] = z;

                                        newcolor = sc.shaderMap.at(modelTri->color)->color;
                                        fb.setPixelColor(newcolor,x,y,framebufferwidth);
                            }
                        }
                    }
                }
            }
        }
    }
fb.export_png("../../test.png");
}



//                                setPixel(*pbuf, x, y, makeColour(r,g,b));
//