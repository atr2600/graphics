//
// Created by brand on 2/6/2019.
//

#include "SceneContainer.h"
#include "Sphere.h"
#include "PerspectiveCamera.h"
#include "Triangle.h"




SceneContainer::SceneContainer() {}

bool SceneContainer::VisibilityQuery(Ray r, double tmin, double tmax){

    HitStruct h;
    for(int i = 0; i<getShapes().size();i++){
        if(getShapes()[i]->intersect(tmin,tmax, h,r)) return true;
    }
    return false;

}

void SceneContainer::addCameras() {

}

void SceneContainer::addLights() {

}

void SceneContainer::addShapes() {

}
//

#include <nlohmann/json.hpp>
#include <fstream>
#include "../src/Vector3D.h"
#include "Lambertian.h"
#include "Box.h"
#include "PointLight.h"
#include "BlinnPhong.h"

//// using this for convenience in specifying the namespace
using json = nlohmann::json;


/**
 * Thank you Pete!!!
 * @param filename
 */
void SceneContainer::parseJSONData(const std::string &filename)
{
    std::cout << "Attempting to parse: " << filename << std::endl;
    std::ifstream inputFileStream( filename );

    // ///////////////////////////////////////
    // open file and parse by json class
    // ///////////////////////////////////////
    json j;
    inputFileStream >> j;

    // ///////////////////////////////////////
    //
    // Loop over all cameras in scene
    //
    // /////////////////////////////////////////
    sivelab::Vector3D p;
    json jsonCameraStructure = j["scene"]["camera"];
    if (jsonCameraStructure.is_array()) {
        std::cout << "Number of cameras: " << jsonCameraStructure.size() << std::endl;

        for (auto i=0; i<jsonCameraStructure.size(); i++) {

            json camInfo = jsonCameraStructure[i];

            sivelab::Vector3D position, viewDir;
            position = camInfo["position"];

            if (!camInfo["lookatPoint"].empty()) {
                sivelab::Vector3D lookAtPoint;
                lookAtPoint = camInfo["lookatPoint"];
                viewDir = lookAtPoint - position;
            }
            else {
                viewDir = camInfo["viewDir"];
            }

            float focalLength = camInfo["focalLength"];
            float imagePlaneWidth = camInfo["imagePlaneWidth"];
            std::string camType = camInfo["_type"];

            if (camType == "perspective") {
                cameras.push_back( new PerspectiveCamera(position, viewDir, focalLength, m_aspectRatio, imagePlaneWidth) );
            }
//            else if (camType == "orthographic") {
//                cameras.push_back( new OrthographicCamera(position, viewDir, focalLength, m_aspectRatio, imagePlaneWidth) );
//            }
        }

    }

    // //////////////////////////////
    //
    // Loop over shaders and place them in a std::map
    //
    // //////////////////////////////
    std::cout << "Number of shaders: " << j["scene"]["shader"].size() << std::endl;
    for (auto i=0; i<j["scene"]["shader"].size(); i++) {

        json shaderInfo = j["scene"]["shader"][i];
        std::string shaderType = shaderInfo["_type"];

        Shader *shaderPtr = nullptr;
        if (shaderType == "Lambertian") {

            sivelab::Vector3D diffuse;
            diffuse = shaderInfo["diffuse"];

            std::cout << "Diffuse = " << diffuse << std::endl;

    //        ShaderCoefficient kd(diffuse, 0);
            shaderPtr = new Lambertian(diffuse);
        }

        else if (shaderType == "BlinnPhong" || shaderType == "Phong") {

            float phongExp;
            sivelab::Vector3D diffuse, specular;
            diffuse = shaderInfo["diffuse"];
            specular = shaderInfo["specular"];
            phongExp = shaderInfo["phongExp"];

//            ShaderCoefficient kd(diffuse, 0);
//            ShaderCoefficient ks(specular, 0);
            if (shaderType == "BlinnPhong")
                shaderPtr = new BlinnPhong(diffuse, specular, phongExp);
        }

        std::string name = shaderInfo["_name"];
        shaderPtr->setName(name);
        shaderMap[name] = shaderPtr;
    }


    // //////////////////////////////////////
    //
    // Loop over all shapes
    //
    // //////////////////////////////////////
    std::cout << "Number of shapes: " << j["scene"]["shape"].size() << std::endl;
    for (auto i=0; i<j["scene"]["shape"].size(); i++) {

        json shapeInfo = j["scene"]["shape"][i];

        Shape *sPtr = nullptr;
        std::string type = shapeInfo["_type"];
        std::string name = shapeInfo["_name"];
        std::string color = shapeInfo["shader"]["_ref"];

        if (type == "sphere") {
            float radius;

            sivelab::Vector3D center;

            center = shapeInfo["center"];
            radius = shapeInfo["radius"];

            sPtr = new Sphere(center[0], center[1], center[2], radius);
        }
        else if (type == "triangle") {
            sivelab::Vector3D v0, v1, v2;
            v0 = shapeInfo["v0"];
            v1 = shapeInfo["v1"];
            v2 = shapeInfo["v2"];

            sPtr = new Triangle(v0, v1, v2);
        }
        else if (type == "box") {
            sivelab::Vector3D minPt, maxPt;

            minPt = shapeInfo["minPt"];
            maxPt = shapeInfo["maxPt"];

            sPtr = new Box(minPt, maxPt);
        }
        
//        else if (type == "mesh") {
//            std::string mesh_filename = shapeInfo["file"];
//            std::string meshFile_fullPath(getFilePath() + "/" + mesh_filename);
//
//            sPtr = new OBJMesh( meshFile_fullPath, m_useBVH );
//        }

        sPtr->setName(name);
        sPtr->setColor(color);


        shapes.push_back(sPtr );
    }


#if 0
    if (type == "box") {

    sivelab::Vector3D minPt, maxPt;

    buf.str( v.second.get<std::string>("minPt") );
    buf >> minPt;
    buf.clear();

    buf.str( v.second.get<std::string>("maxPt") );
    buf >> maxPt;
    buf.clear();

    sPtr = new Box(minPt, maxPt);
    sPtr->setName(name);
    sPtr->provideShader( shaderPtr );
  }



#endif


    // Walk over all ligths
    std::cout << "Number of lights: " << j["scene"]["light"].size() << std::endl;
    for (auto i=0; i<j["scene"]["light"].size(); i++) {

        std::string type = j["scene"]["light"][i]["_type"];

        sivelab::Vector3D position, radiantEnergy;
        position = j["scene"]["light"][i]["position"];
        radiantEnergy = j["scene"]["light"][i]["intensity"];

        // if ( type == "point" )
        lights.push_back( new PointLight(position, radiantEnergy) );

    }
}

std::vector<Camera *> &SceneContainer::getCameras() {
    return cameras;
}

std::vector<Light *> &SceneContainer::getLights() {
    return lights;
}

std::vector<Shape *> &SceneContainer::getShapes() {
    return shapes;
}

std::map<std::string, Shader *> &SceneContainer::getShaders() {
    return shaderMap;
}
