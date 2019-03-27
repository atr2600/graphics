INCLUDE_DIRECTORIES( ${CMAKE_SRC_DIR}/src)
INCLUDE_DIRECTORIES( $(CMAKE_SRC_DIR)/json-develop)
include_directories(${CMAKE_SOURCE_DIR}/raytrace)
include_directories(${CMAKE_SOURCE_DIR}/renderer)

INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
link_libraries (${OPENGL_LIBRARY})
include_directories(${GLFW_INCLUDE_DIRS})

add_library (renderer-util
        Camera.cpp Camera.h
        CoordinateSystem.cpp CoordinateSystem.h
        framebuffer.h framebuffer.cpp
        Light.cpp Light.h
        NormalShader.cpp NormalShader.h
        PerspectiveCamera.cpp PerspectiveCamera.h
        PointLight.cpp PointLight.h
        Ray.cpp Ray.h
        SceneContainer.cpp SceneContainer.h
        Shape.cpp Shape.h
        Shader.cpp Shader.h
        Sphere.cpp Sphere.h
        HitStruct.cpp HitStruct.h
        Scene_jsonParser.cpp Triangle.cpp Triangle.h
        Lambertian.cpp Lambertian.h BlinnPhong.cpp BlinnPhong.h
        Mirror.cpp Mirror.h Box.cpp Box.h renderer.h RendererBasic.cpp
        RendererBasic.h RendererOpenGL.cpp RendererOpenGL.h
        )

#target_link_libraries(run renderer-util sive-util)
#
#target_link_libraries (run ${GLEW_LIBRARIES})
#target_link_libraries (run glfw ${GLFW_STATIC_LIBRARIES})
#target_link_libraries(run sive-util)
#target_link_libraries(run renderer-util)
#target_link_libraries(run ${Boost_PROGRAM_OPTIONS_LIBRARIES})
#target_link_libraries(run ${PNG_LIBRARY})
#target_link_libraries(run ${ZLIB_LIBRARY})
#target_link_libraries(run ${OPENGL_LIBRARY})