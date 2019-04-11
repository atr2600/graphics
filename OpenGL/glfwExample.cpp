#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLSL.h"

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLSL.h"

int CheckGLErrors(const char *s)
{
    int errCount = 0;

    return errCount;
}

int main(void)
{
    //This is for windows, if you are running linux you want to comment line 26 out. Need to
    // to make a argument to set this one.
//    setenv("DISPLAY", "127.0.0.1:0", true);
    //
    // INITIALIZATION PART
    //
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
    float aspectRatio = 1; // winWidth / (float)winHeight;
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

    glClearColor(0.5, 0.5, 0.5, 1.0);

    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);

    GLint major_version;
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    std::cout << "GL_MAJOR_VERSION: " << major_version << std::endl;

    // 
    // RENDER LOOP
    //
    double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;
    // Reference Step 1 above
    GLuint m_triangleVBO;
    glGenBuffers(1, &m_triangleVBO);

// Reference Step 2 above
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);

// The following code allocates memory on the host to hold
// the vertices in the CPU host memory.  We use the std::vector
// initialization list to set the vertex data:
    std::vector< float > host_VertexBuffer{ 0.0f, 3.0f, 0.0f,   // V0
                                            1.0f, 0.0f, 0.0f,   // Red for V0
                                            -3.0f, -3.0f, 0.0f, // V1
                                            0.0f, 1.0f, 0.0f,   // Green for V1
                                            3.0f, -3.0f, 0.0f,  // V2
                                            0.0f, 0.0f, 1.0f }; // Blue for V2;
    int numBytes = host_VertexBuffer.size() * sizeof(float);

// Reference Step 3 above
    glBufferData(GL_ARRAY_BUFFER, numBytes, host_VertexBuffer.data(), GL_STATIC_DRAW);

// Once the data has been copied to the GPU, it can safely be deleted from the host
// memory.
    host_VertexBuffer.clear();
    GLuint m_VAO;
    glGenVertexArrays(1, &m_VAO);  // Step 1 above
    glBindVertexArray(m_VAO);      // Step 2 above


    glEnableVertexAttribArray(0);  // enable attrib 0 (Step 3)
    glEnableVertexAttribArray(1);  // enable attrib 1 - Vertex color

    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);  // Step 4
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);  // Step 5
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const GLvoid *)12);  // Color


// When done binding a VAO, you can unbind it by passing 0 to the bind call
    glBindVertexArray(0);

    sivelab::GLSLObject shader;

    shader.addShader( "../../OpenGL/vertexShader_perVertexColor.glsl", sivelab::GLSLObject::VERTEX_SHADER );
    shader.addShader( "../../OpenGL/fragmentShader_perVertexColor.glsl", sivelab::GLSLObject::FRAGMENT_SHADER );
    shader.createProgram();
    GLuint projMatrixID = shader.createUniform( "projMatrix" );  // gets reference to projMatrix var


    float left = -4.5;
    float right = 3.0;
    float bottom = -4.0;
    float top = 4.0;
    float near = -4.0;
    float far = 3.0;

    // you can ONLY set the data for a uniform variable when the shader is bound, so
    // make sure to activate it first:

    glm::mat4 projMatrix = glm::ortho(left, right, bottom, top, near, far);
    shader.activate();
    glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr(projMatrix));

    glfwMakeContextCurrent(window);

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

