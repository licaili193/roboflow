cmake_minimum_required(VERSION 3.1.0)

project(remote_control)

set (CMAKE_CXX_STANDARD 14)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Universial dependency:

# GLog
find_package(Glog REQUIRED)
include_directories(${GLOG_INCLUDE_DIRS}) 

# GFlags
find_package (gflags REQUIRED)
include_directories (${gflags_INCLUDE_DIR})

# Yaml-cpp
find_package (yaml-cpp REQUIRED)
include_directories (${YAML_CPP_INCLUDE_DIR})

# Thread
find_package(Threads REQUIRED)

# Blend2d
set(BLEND2D_DIR "${CMAKE_SOURCE_DIR}/src/third_party/blend2d")
set(ASMJIT_DIR "${CMAKE_SOURCE_DIR}/src/third_party/asmjit")
set(BLEND2D_STATIC TRUE)
include("${BLEND2D_DIR}/CMakeLists.txt")

# Eigen
set(EIGEN_DIR "${CMAKE_SOURCE_DIR}/src/third_party")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(src)