#! /bin/bash

cmake

cd main/

make

./run -w 250 -h 250 -i ../renderer/sceneData/scenes_A/spheres_1K.json -o ../../main/main.png