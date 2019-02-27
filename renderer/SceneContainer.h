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
    std::vector<Camera*> cameras;
    std::vector<Light*> lights;
    std::vector<Shape*> shapes;
    std::map<std::string, Shader*> shaders;
public:
    const std::vector<Camera *> &getCameras() const;

    const std::vector<Light *> &getLights() const;

    const std::vector<Shape *> &getShapes() const;

    const std::map<std::string, Shader *> &getShaders() const;

private:
    double m_aspectRatio = 1;
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

    void parseJSONData(const std::string &filename);


};


#endif //OPENGL_FCG_SCENECONTAINER_H
