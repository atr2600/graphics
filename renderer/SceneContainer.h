//
// Created by brand on 2/6/2019.
//

#ifndef OPENGL_FCG_SCENECONTAINER_H
#define OPENGL_FCG_SCENECONTAINER_H

#include <vector>
#include "Camera.h"
#include "Light.h"
#include "Shape.h"
#include <map>
#include "Shader.h"


/**
 * Scene Container. 
 */
class SceneContainer {
    /**
     *
     */
private:
    std::vector<Camera*> allCameras;
    std::vector<Light*> allLights;
    std::vector<Shape*> allShapes;
    std::map<std::string, Shader*> allShaders;
    /**
     *
     */
public:
    /**
     *
     */
    SceneContainer();
    /**
     * Add a shape to the class.
     */
    void addShapes();
    /**
     * Add a light to the class.
     */
    void addLights();
    /**
     * Add a Camera to the class.
     */
    void addCameras();

};


#endif //OPENGL_FCG_SCENECONTAINER_H
