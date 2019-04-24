#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLSL.h"

using namespace glm;

int CheckGLErrors(const char *s)
{
    int errCount = 0;
    
    return errCount;
}

int main(void)
{


    // 
    // INITIALIZATION PART
    //
        setenv("DISPLAY", "127.0.0.1:0", true);
    /* Initialize the library */
    if (!glfwInit())
        exit (-1);
    // throw std::runtime_error("Error! initialization of glfw failed!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    int winWidth = 1000;
    float aspectRatio = 16.0 / 9.0; // winWidth / (float)winHeight;
    int winHeight = winWidth / aspectRatio;

    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "FCG4E Examples", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW did not create a window!" << std::endl;

        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err=glewInit();
    if(err != GLEW_OK) {
        std::cerr <<"GLEW Error! glewInit failed, exiting."<< std::endl;
        exit(EXIT_FAILURE);
    }

    const GLubyte* renderer = glGetString (GL_RENDERER);
    const GLubyte* version = glGetString (GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.75, 0.75, 0.75, 1.0);

    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);

    GLint major_version;
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    std::cout << "GL_MAJOR_VERSION: " << major_version << std::endl;


    ////////////////// VBO //////////////////////////////
// Reference Step 1 above
    GLuint m_triangleVBO;
    glGenBuffers(1, &m_triangleVBO);

// Reference Step 2 above
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);

// The following code allocates memory on the host to hold
// the vertices in the CPU host memory.  We use the std::vector
// initialization list to set the vertex data:
    double left, right, bottom, top, near, far;
    left = -7.5;
    right = 7.5;
    bottom = -4.2;
    top = 4.2;
    near = -10.0;
    far = 10.0;

//    vec3 n = normalize(Normal_camerspace);
//    vec3 l = normalize( LightDirection_cameraspace );

    vec3 v0 = vec3(0.75f, 0.5f, 0.0f);
    vec3 v1 = vec3(-0.5f, 0.1f, 0.0);
    vec3 v2 = vec3(-1.0f, 0.5f, 0.0f);
    vec3 normal = cross((v1-v0),(v2-v0));
    normalize(normal);
    normal[0]=normal[0]*0.5+0.5;
    normal[1]=normal[1]*0.5+0.5;;
    normal[2]=normal[2]*0.5+0.5;;
    std::cout << (normal[0]) << normal[1] << normal [2];

    std::vector< float > host_VertexBuffer{ v0[0], v0[1], v0[2],    // V0
                                            normal[0], normal[1], normal[2],
                                            v1[0], v1[1], v1[2],
                                            normal[0], normal[1], normal[2],
                                            v2[0], v2[1], v2[2],
                                            normal[0], normal[1], normal[2]};    // V2
    int numBytes = host_VertexBuffer.size() * sizeof(float);

// Reference Step 3 above
    glBufferData(GL_ARRAY_BUFFER, numBytes, host_VertexBuffer.data(), GL_STATIC_DRAW);

// Once the data has been copied to the GPU, it can safely be deleted from the host
// memory.
    host_VertexBuffer.clear();


    //////////////////////////////////////////  VAO ///////////////////////////////
    GLuint m_VAO;
    glGenVertexArrays(1, &m_VAO);  // Step 1 above
    glBindVertexArray(m_VAO);      // Step 2 above

    glEnableVertexAttribArray(0);  // enable attrib 0 - Vertex Position
    glEnableVertexAttribArray(1);  // enable attrib 1 - Vertex color

    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);  // Step 4
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const GLvoid *)12);  // Color

    glBindVertexArray(0);


// When done binding a VAO, you can unbind it by passing 0 to the bind call
    glBindVertexArray(0);

    sivelab::GLSLObject shader;
    shader.addShader( "../../OpenGL/vertexShader_normal.glsl", sivelab::GLSLObject::VERTEX_SHADER );
    shader.addShader( "../../OpenGL/fragmentShader_normal.glsl", sivelab::GLSLObject::FRAGMENT_SHADER );
    shader.createProgram();
    GLuint projMatrixID = shader.createUniform( "projMatrix" );  // gets reference to projMatrix var

    // you can ONLY set the data for a uniform variable when the shader is bound, so
    // make sure to activate it first:
    shader.activate();
    mat4 projMatrix = ortho(left, right, bottom, top, near, far);
    glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, value_ptr(projMatrix));

    // 
    // RENDER LOOP
    //
    double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        endFrameTime = glfwGetTime();
        timeDiff = endFrameTime - startFrameTime;
        startFrameTime = glfwGetTime();

        // Clear the window's buffer (or clear the screen to our
        // background color)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* Render stuff here */

        //////////////////////////////  RENDER
        shader.activate();  // bind the shader that will process the vertices and fragments

        glBindVertexArray(m_VAO);            // bind the VAO
        glDrawArrays(GL_TRIANGLES, 0, 3);    // tell OpenGL to render it
        glBindVertexArray(0);

        shader.deactivate(); // unbind the shader so it doesn't affect other vertex data

        // Swap the front and back buffers
        // glfwSwapInterval(0);
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

#if 0
        // Here are some other examples for polling the keys...
        if (glfwGetKey( window, GLFW_KEY_1 ) == GLFW_PRESS) {
            // if key 1 is pressed do something
        }
        else if (glfwGetKey( window, GLFW_KEY_2 ) == GLFW_PRESS) {
            // if key 2 is pressed do something  else...
        }
#endif

        if (glfwGetKey( window, GLFW_KEY_T ) == GLFW_PRESS) {
            std::cout << "fps: " << 1.0/timeDiff << std::endl;
        }

        if (glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, 1);
    }
  
    glfwTerminate();
    return 0;
}

