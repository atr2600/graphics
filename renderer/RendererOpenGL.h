//
// Created by brand on 3/26/2019.
//

#ifndef OPENGL_FCG_RENDEREROPENGL_H
#define OPENGL_FCG_RENDEREROPENGL_H


#include "renderer.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "../OpenGL/GLSL.h"
#include "framebuffer.h"


class RendererOpenGL: public renderer {
public:
    RendererOpenGL(const SceneContainer &sc, int framebufferwidth, int framebufferheight);

    int render();
};


#endif //OPENGL_FCG_RENDEREROPENGL_H
