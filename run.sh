#! /bin/bash

cmake .

cd main/

make -j

./run -w 250 -h 250 -r 1 -i ../renderer/sceneData/scenes_A/spheres_1K.json -o ../spheres_1k.png
./run -w 250 -h 250 -r 1 -i ../renderer/sceneData/scenes_A/spheresAndTriangles.json -o ../spheresAndTriangles.png
./run -w 250 -h 250 -r 1 -i ../renderer/sceneData/scenes_A/oneTriangle.json -o ../oneTriangle.png
./run -w 250 -h 250 -r 1 -i ../renderer/sceneData/scenes_A/lambertianChalkSpheres.json -o ../lambertianChalkSpheres.png
./run -w 250 -h 250 -r 1 -i ../renderer/sceneData/scenes_A/PhongExp.json -o ../PhongExp.png
./run -w 250 -h 250 -r 1 -i ../renderer/sceneData/scenes_A/threeTriangles.json -o ../threeTriangles.png
./run -w 250 -h 250 -r 1 -i ../renderer/sceneData/scenes_A/oneSphere.json -o ../oneSphere.png
./run -w 250 -h 250 -r 4 -i ../renderer/sceneData/scenes_B/areaLight.json -o ../areaLight.png
