#! /bin/bash

cmake .

cd main/

make -j

./run -w 250 -h 250 -i ../renderer/sceneData/scenes_A/spheres_1K.json -o ../spheres_1k.png
./run -w 250 -h 250 -i ../renderer/sceneData/scenes_A/lotsOTriangles.json -o ../lotsOTriangles.png
./run -w 250 -h 250 -i ../renderer/sceneData/scenes_A/oneTriangle.json -o ../oneTriangle.png
./run -w 250 -h 250 -i ../renderer/sceneData/scenes_A/lambertianChalkSpheres.json -o ../lambertianChalkSpheres.png
./run -w 250 -h 250 -i ../renderer/sceneData/scenes_A/PhongExp.json -o ../PhongExp.png
./run -w 250 -h 250 -i ../renderer/sceneData/scenes_A/threeTriangles.json -o ../threeTriangles.png
./run -w 250 -h 250 -i ../renderer/sceneData/scenes_A/oneSphere.json -o ../oneSphere.png
./run -w 250 -h 250 -i ../renderer/sceneData/scenes_A/mirrorScene00.json -o ../mirrorScene1.png
./run -w 250 -h 250 -i ../renderer/sceneData/scenes_A/mirrorScene01.json -o ../mirrorScene2.png
./run -w 250 -h 250 -i ../renderer/sceneData/scenes_A/simpleSphereScene.json -o ../simpleSphere.png
