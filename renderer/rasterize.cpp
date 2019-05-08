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
    double l,r,b,t,n,f;
    l = -1;
    b = -1;
    n = -1;
    r = 1;
    t = 1;
    f = 1;

    Matrix4x4 Mvp ((width/2),(0)   ,(0),((width-1)/2),
                              (0)   ,(height/2),(0),((height-1)/2),
                              (0)   ,(0)   ,(1),(0),
                              (0)   ,(0)   ,(0),(1));
    sivelab::Vector3D U = sc.cameras[0]->csys.getU();
    sivelab::Vector3D V = sc.cameras[0]->csys.getU();
    sivelab::Vector3D W = sc.cameras[0]->csys.getU();
    sivelab::Vector3D E = sc.cameras[0]->position;
//    Matrix4x4 Morth = Matrix4x4((2/(r-l)),(0),(0),(-(r+l)/(r-l)),
//                                (0),(2/(t-b)),(0),(-(t+b)/(t-b)),
//                                (0),(0),(2/(n-f)),(-(n+f)/(n-f)),
//                                (0),(0),(0),(1));
    Matrix4x4 Morth (U[0],U[1],U[2],0,
                                V[0],V[1],V[2],0,
                                W[0],W[1],W[2],0,
                                0   ,0   ,0   ,1);
    Matrix4x4 tempCam (1,0,0,-1*E[0],
                                  0,1,0,-1*E[1],
                                  0,0,1,-1*E[2],
                                  0,0,0,1);

    Matrix4x4 Mcam = Morth * tempCam;

    Matrix4x4 Mp = Matrix4x4(n,0,0,0,
                             0,n,0,0,
                             0,0,n+f,-1*f*n,
                             0,0,0,1);

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
        M = Mvp * Morth * Mp;
        std::vector<sivelab::Vector3D> triPoints;
        std::vector<sivelab::Vector3D> colors;
        Shape* currentTriangle = sc.shapes[index];

        for(int sides = 0; sides < 3; sides++){
            sivelab::Vector3D vCam = Mcam.multVector(Mlocal.multVector(currentTriangle->getVertex(sides),one),one);

            std::vector<PointLight> newLights;

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
            triPoints[sides] /= one;
        }

//
//        // For barycentric coordinates
//        for(int i = 0; i < 3; i++ ) {
//            b[i] = nx[i] * ( sx[(i+2)%3] - sx[i] ) + ny[i] * ( sy[(i+2)%3] - sy[i] );
//        }

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

//        if(ymin > ymax || xmin > xmax) {
//            continue;
//        }

        sivelab::Vector3D finalColor;

        float factAlpha = f12(triPoints[1],triPoints[2],triPoints[0][0],triPoints[1][0]);
        float factBeta = f20(triPoints[2],triPoints[0],triPoints[0][1],triPoints[1][1]);
        float factGama = f01(triPoints[0],triPoints[1],triPoints[0][2],triPoints[1][2]);


        // Draw pixels inside, if need be
        for( int y = ymin; y < ymax; y++ ) {
            for( int x = xmin; x < xmax; x++ ) {
                float alpha;
                float beta;
                float gamma;
                if(factAlpha == 0){
                    alpha = 0;
                } else {
                    alpha = f12(triPoints[1],triPoints[2],x,y)/factAlpha;
                }
                if ( factBeta == 0){
                    beta = 0;
                } else {
                    beta = f20(triPoints[2], triPoints[0],x,y)/factBeta;
                }
                if (factGama == 0){
                    gamma = 0;
                } else {
                    gamma = f01(triPoints[0],triPoints[1],x,y)/factGama;
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

//float rasterize::baryCords(sivelab::Vector3D v0, sivelab::Vector3D v1, sivelab::Vector3D v2, sivelab::Vector3D P, int option){
//    if(option == 1){
//        return (v1[1] - v2[1])*(v0[0] - v2[0]) + (v2[0] - v1[0])*(v0[1] - v2[1]);
//    }
//    if(option == 2){
//        return (v1[1] - v2[1])*(P[0] - v2[0]) + (v2[0] - v1[0])*(P[1] - v2[1]);
//    }
//    if(option == 3){
//        return (v2[1] - v0[1])*(P[0] - v2[0]) + (v0[0] - v2[0])*(P[1] - v2[1]);
//    }
//
//
//}

float rasterize::f01(sivelab::Vector3D v0, sivelab::Vector3D v1, int x, int y){

    // f01(x,y) = (y0-y1) x + (x1-x0) y + x-y1 - x1y0

    return ((v1[0]-v1[1])*x) + ((v0[1] - v0[0]) * y) + (v0[0]*v1[1]) - (v0[1]*v1[0]);
}
float rasterize::f12(sivelab::Vector3D v0, sivelab::Vector3D v1, int x, int y){
    return ((v1[1]-v1[2])*x) + ((v0[2] - v0[1]) * y) + (v0[1]*v1[2]) - (v0[2]*v1[1]);
}
float rasterize::f20(sivelab::Vector3D v0, sivelab::Vector3D v1, int x, int y){
    return ((v1[2]-v1[0])*x) + ((v0[0] - v0[2]) * y) + (v0[2]*v1[0]) - (v0[0]*v1[2]);
}

