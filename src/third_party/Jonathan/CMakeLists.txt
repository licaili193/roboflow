cmake_minimum_required(VERSION 3.1.0)

project(jonathan_contour)

add_library(jonathan_contour
    Contour.cpp
    ListContour.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})