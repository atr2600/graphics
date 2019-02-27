INCLUDE_DIRECTORIES( ${CMAKE_SRC_DIR}/src)
INCLUDE_DIRECTORIES( $(CMAKE_SRC_DIR)/json-develop)
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
        Scene_jsonParser.cpp Triangle.cpp Triangle.h Lambertian.cpp Lambertian.h)

target_link_libraries(renderer-util sive-util)