INCLUDE_DIRECTORIES( ${CMAKE_SRC_DIR}/src)
INCLUDE_DIRECTORIES( $(CMAKE_SRC_DIR)/json-develop)
include_directories(${CMAKE_SOURCE_DIR}/raytrace)
include_directories(${CMAKE_SOURCE_DIR}/renderer)

INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
link_libraries (${OPENGL_LIBRARY})
include_directories(${GLFW_INCLUDE_DIRS})

add_executable(run
        run.cpp
        SafeQueue.h ThreadPool.h)

target_link_libraries(run renderer-util sive-util)

target_link_libraries (run ${GLEW_LIBRARIES})
target_link_libraries (run glfw ${GLFW_STATIC_LIBRARIES})
target_link_libraries(run sive-util)
target_link_libraries(run renderer-util)
target_link_libraries(run ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(run ${PNG_LIBRARY})
target_link_libraries(run ${ZLIB_LIBRARY})
target_link_libraries(run ${OPENGL_LIBRARY})

