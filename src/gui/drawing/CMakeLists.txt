cmake_minimum_required(VERSION 3.1.0)

project(drawing)

add_library(drawing_widgets
    AxisWidget.cpp
    DrawableWidget.cpp
    CanvasWidget.cpp
)
target_link_libraries(drawing_widgets 
    Blend2D::Blend2D
    navigation_function_math
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})