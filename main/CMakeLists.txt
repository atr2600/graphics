#
# Adds the src directory to the include search
# path. ${CMAKE_SOURCE_DIR} is prefixed to allow the files in the
# utest directory to correctly include the relative reference to the
# src files.
#
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/raytrace)
include_directories(${CMAKE_SOURCE_DIR}/renderer)

add_executable(run
        run.cpp
        )
target_link_libraries(run sive-util)
target_link_libraries(run renderer-util)
target_link_libraries(run ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(run ${PNG_LIBRARY})
target_link_libraries(run ${ZLIB_LIBRARY})

