cmake_minimum_required(VERSION 3.1.0)

project(contour)

add_library(contour_plot
    ContourPlot.cpp
)
target_link_libraries(contour_plot 
    Blend2D::Blend2D
    jonathan_contour
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})