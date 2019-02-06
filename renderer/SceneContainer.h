/**
 * \class SceneContainer
 *
 * \ingroup render_util
 *
 * \brief Computer Graphics class.
 *
 *
 *
 * \note University of Minnesota Duluth Computer Graphics
 *
 * \author (last to touch it) $Author: bv Brandon Geraci$
 *
 * \version $Revision: 0.0 $
 *
 * \date $Date: 2019/02/06 8:16:20 $
 *
 * Contact: bran0847@d.umn.edu
 *
 * Created on: Wed Feb 6 18:39:37 2019
 *
 */

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
