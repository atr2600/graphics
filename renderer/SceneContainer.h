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
    std::map<std::string, Shader*> shaderMap;
    sivelab::Vector3D background;
public:
    std::vector<Camera *> &getCameras() ;

    std::vector<Light *> &getLights();

    std::vector<Shape *> &getShapes() ;

    std::map<std::string, Shader *> &getShaders() ;

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

    const Vector3D &getBackground() const;

    void setBackground(const Vector3D &background);

    /**
     * Add a Camera to the class.
     */
    void addCameras();

    void parseJSONData(const std::string &filename);

    bool VisibilityQuery(Ray r, double tmin, double tmax);


};


#endif //OPENGL_FCG_SCENECONTAINER_H
