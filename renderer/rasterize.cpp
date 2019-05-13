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
#include "../src/Matrix4x4.h"
#include "PointLight.h"
#include "HitStruct.h"


rasterize::rasterize(const SceneContainer &sc, int framebufferwidth, int framebufferheight) : renderer(sc,
                                                                                                       framebufferwidth,
                                                                                                       framebufferheight) {

//    int nx = framebufferwidth;
//    int ny = framebufferheight;
    int width = framebufferwidth;
    int height = framebufferheight;
    float l,r,b,t,n,f;
    f = 1000;
    n = 1;
    r = (sc.cameras[0]->imagePlaneWidth/2.0)/sc.cameras[0]->focalLength;
    t = (sc.cameras[0]->imagePlaneHeight/2.0)/sc.cameras[0]->focalLength;
    l = -1.0 * r;
    b = -1.0 * t;

    Matrix4x4 Mvp ((width/2.0),(0)   ,(0),((width-1)/2.0),
                              (0)   ,(height/2.0),(0),((height-1)/2.0),
                              (0)   ,(0)   ,(1),(0),
                              (0)   ,(0)   ,(0),(1));
    sivelab::Vector3D U = sc.cameras[0]->csys.getU();
    sivelab::Vector3D V = sc.cameras[0]->csys.getU();
    sivelab::Vector3D W = sc.cameras[0]->csys.getU();
    sivelab::Vector3D E = sc.cameras[0]->position;
    Matrix4x4 M1           (U[0],U[1],U[2],0,
                                V[0],V[1],V[2],0,
                                W[0],W[1],W[2],0,
                                0   ,0   ,0   ,1);
    Matrix4x4 M2                (1,0,0,-1*E[0],
                                  0,1,0,-1*E[1],
                                  0,0,1,-1*E[2],
                                  0,0,0,1);
// page 160 in the text book.
    Matrix4x4 Mcam = M1 * M2;

    Matrix4x4 Mper = Matrix4x4((2*n)/(r-l),0,(l+r)/(l-r),0,
                             0,(2*n)/(t-b),(b+t)/(b-t),0,
                             0,0,(f+n)/(n-f),(2*f*n)/(f-n),
                             0,0,1,0);

    Matrix4x4 Mlocal;

    Mlocal.setIdentity();

    Matrix4x4 M;
    std::vector<Shape*> newTriangles;

    int xmin;
    int xmax;
    int ymin;
    int ymax;
    
    Matrix4x4 test;

    framebuffer fb = framebuffer(height,width);
    /**
     * Set the color of the background.
     */
    for(int i = 0; i < height; i++){
        for (int j = 0; j < height; j++){
            fb.setPixelColor(sivelab::Vector3D(0.75,0.75,0.75),j,i,width);
        }
    }
    float zbuf[width][height];

    /**
     * This is my Z-BUFFER.. depth buffer.
     */
    for(int y = 0; y < framebufferheight; y++ ) {
        for(int x = 0; x < framebufferwidth; x++ ) {
            zbuf[y][x] = -99999999;
        }
    }



    // Status variables.
    Shape* currentTriangle;
    float d1;
    float d2;
    float d3;
    double one = 1;
    float z;
    Ray ray = Ray(sc.cameras[0]->direction,sc.cameras[0]->position);
    HitStruct hit;
    std::map<std::string, Shader*> copyShaders = sc.shaderMap;
    // The actual rasterizer.
    std::vector<Light *> copyLight = sc.lights;
    for(int index = 0; index < sc.shapes.size(); index++) {
        one = 1;
        M = Mvp * Mper *  Mcam;
        std::vector<sivelab::Vector3D> triPoints;
        std::vector<sivelab::Vector3D> colors;
        Shape* currentTriangle = sc.shapes[index];

        for(int verts = 0; verts < 3; verts++){
            ///////////////////////// FIGURE THIS PART OUT ////////////////////
            ///////// I CHANGED IT BUT BROKE IT.... /////////////////////////
            Matrix4x4 vCam = Mcam * Mlocal * verts;

            std::vector<PointLight> newLights;
            std::cout << one;
            for(int cur = 0; cur < sc.lights.size(); cur++){
                sivelab::Vector3D pos = Mcam.multVector(sc.lights[cur]->getPosition(),one);
                PointLight fire(pos, sc.lights[cur]->getIntensity());
                newLights.push_back(fire);
            }
            for(int k = 0; k < newLights.size(); k++){
                colors.push_back(sc.shaderMap.at(currentTriangle->color)->applyShader(ray,copyLight,hit,copyShaders,0,0,
                                                                                      nullptr));
            }
            triPoints.push_back(M.multVector(vCam,one));
            triPoints[verts] /= one;
        }

        // Bounding rectangles.
        xmin = floor( fmin( fmin( triPoints[0][0], triPoints[0][1] ), triPoints[0][2] ) );
        ymin = floor( fmin( fmin( triPoints[1][0], triPoints[1][1] ), triPoints[1][2] ) );
        xmax = ceil( fmax( fmax( triPoints[0][0], triPoints[0][1] ), triPoints[0][2] ) );
        ymax = ceil( fmax( fmax( triPoints[1][0], triPoints[1][1] ), triPoints[1][2] ) );

        // Clip and possibly rejec
        xmin = fmax(0, xmin);
        xmax = fmin(width, xmax);
        ymin = fmax(0, ymin);
        ymax = fmin(height, ymax);

        sivelab::Vector3D finalColor;

        float factAlpha = line(triPoints[1],triPoints[2],triPoints[0][0],triPoints[0][1]);
        float factBeta = line(triPoints[2],triPoints[0],triPoints[1][0],triPoints[1][1]);
        float factGama = line(triPoints[0],triPoints[1],triPoints[2][0],triPoints[2][1]);


        // Draw pixels inside, if need be
        for( int y = ymin; y < ymax; y++ ) {
            for( int x = xmin; x < xmax; x++ ) {
                float alpha;
                float beta;
                float gamma;
                if(factAlpha == 0){
                    alpha = 0;
                } else {
                    alpha = line(triPoints[1],triPoints[2],x,y)/factAlpha;
                }
                if ( factBeta == 0){
                    beta = 0;
                } else {
                    beta = line(triPoints[2], triPoints[0],x,y)/factBeta;
                }
                if (factGama == 0){
                    gamma = 0;
                } else {
                    gamma = line(triPoints[0],triPoints[1],x,y)/factGama;
                }

                finalColor.set(0,0,0);
                if(alpha >= 0 && beta >= 0 && gamma >= 0) {
                    finalColor += (colors[0] * alpha) + (colors[1] * beta) + (colors[2] * gamma);
                    if( d2 >= 0 ) {
                        float curZ = triPoints[0][2]*alpha + triPoints[1][2]*beta + triPoints[2][2]*gamma;

                        if (x >= 0 && y >= 0 && x < width && y < height) { //Check bounds of image

                            float depth = triPoints[0][2]*alpha + triPoints[1][2]*beta + triPoints[2][2]*gamma;

                            if(depth > zbuf[x][y]) {
                                zbuf[x][y] = depth;
                                fb.setPixelColor(finalColor,x,y,width);
                            }

                        }

                    }
                }
            }
        }
    }
fb.export_png("../../test.png");
}

float rasterize::line(sivelab::Vector3D v0, sivelab::Vector3D v1, float x, float y){
    return ((v1[0]-v1[1])*x + (v0[1]-v0[0])*y + (v0[0]*v1[1]) - (v0[1]*v1[0]));
}
