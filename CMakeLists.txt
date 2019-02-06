CMAKE_MINIMUM_REQUIRED (VERSION 3.1)

PROJECT (OpenGL_FCG)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH})

Include(ExtraMacros)
APPEND_TO_STRING(CXX_FLAGS "-std=c++11")

# --------------------------------------------------------------------
# PNG and ZLIB
# 
# This macro will attempt to locate the PNG include directories, link
# directories and libraries. The INCLUDE_DIRECTORIES macro adds the
# resulting include directories to the search path.
# --------------------------------------------------------------------
find_package(PNG REQUIRED)
if (PNG_FOUND)
  MESSAGE(STATUS "PNG Version: ${PNG_VERSION_STRING}, Includes: ${PNG_INCLUDE_DIR}, Libs: ${PNG_LIBRARIES}")
  INCLUDE_DIRECTORIES(${PNG_INCLUDE_DIR})
else (PNG_FOUND)
  MESSAGE(STATUS "Could not find the PNG Libraries!")
endif (PNG_FOUND)

# --------------------------------------------------------------------
# OpenGL Related Components
# --------------------------------------------------------------------
FIND_PACKAGE(OpenGL REQUIRED)

FIND_PACKAGE(GLEW REQUIRED)
MESSAGE(STATUS "GLEW: incs= ${GLEW_INCLUDE_DIR}, libs= ${GLEW_LIBRARIES}")
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIR})

# FROM https://github.com/nlohmann/json
# 
# Typically you don't care so much for a third party library's tests to be
# run from your own project's code.
set(JSON_BuildTests OFF CACHE INTERNAL "")

# From nlohmann_json README: Don't use
# include(nlohmann_json/CMakeLists.txt) since that carries with it
# unintended consequences that will break the build.  It's generally
# discouraged (although not necessarily well documented as such) to
# use include(...) for pulling in other CMake projects anyways.
add_subdirectory(json-develop)

# Add the path to the OptiX headers to our include paths.
include_directories(
  "json-develop/include"
  )

# To be able to include the GLFW header from your code, you need to
# tell the compiler where to find it.
add_subdirectory(${CMAKE_SOURCE_DIR}/glfw-master)

# Once GLFW has been added to the project, the GLFW_LIBRARIES cache
# variable contains all link-time dependencies of GLFW as it is
# currently configured. To link against GLFW, link against them and
# the glfw target.
include_directories(${CMAKE_SOURCE_DIR}/glfw-master/include)
MESSAGE(STATUS "${GLFW_LIBRARIES}")
SET(GLFW_STATIC_LIBRARIES "${GLFW_LIBRARIES}")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/glm-0.9.9.3)

# ----------------------------------------------------------
# Boost
#
# This section tests for Boost support on the system. Boost is
# required as it is used heavily with this code. Boost also allows the
# code to be nicely portable across Operating Systems.
# ----------------------------------------------------------
# SET (Boost_MULTITHREADED TRUE)

# If you want to get more info on what the Find Boost macro is
# doing...  
# SET(Boost_DEBUG 1)

# Necessary to get Win32 version to work, plus, not a bad idea to link
# statically for our purposes.
SET(Boost_USE_STATIC_LIBS TRUE)

FIND_PACKAGE(Boost REQUIRED date_time program_options system thread unit_test_framework chrono timer)
IF(${Boost_FOUND})
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
  MESSAGE(STATUS "Boost Libs: ${Boost_LIBRARIES}")
ENDIF()

# Add the src directory to build the libsive-util.a library.
add_subdirectory(src)

#add_subdirectory(src/renderer)
add_subdirectory(renderer)

# If you want, we can also compile the tests directory that are
# essentially examples for how to use some of the classes and code.
add_subdirectory(examples)

#
# Rendering Code
# 
# add_subdirectory(renderer)

#
# OpenGL Example
#
# This builds a simple OpenGL example that you can use to get started with OpenGL.
#
# add_subdirectory(OpenGL)

#
# Unit Tests - by enabling testing with cmake, we can create a target
# that lets unit tests be run. After re-building yourproject with
# ENABLE_TESTING called, a make target, called test will be
# enabled. You can then type
# 
#  make test
#
# to perform the unit tests. See the CMakeLists.txt file in the utests
# directory for more details. Also, see the unit test .cpp files in
# the utests directory for examples on using Boost's unit test system.
#
ENABLE_TESTING()
add_subdirectory(utests)
