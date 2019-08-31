cmake_minimum_required(VERSION 3.1.0)

project(drawing)

add_library(drawing_widgets
    AxisWidget.cpp
    DrawableWidget.cpp
    CanvasWidget.cpp
)
target_link_libraries(drawing_widgets 
    Blend2D::Blend2D
    navigation_function
    navigation_function_drawer
)

add_library(navigation_function_drawer
    NavigationFunctionDrawer.cpp
)
target_link_libraries(navigation_function_drawer 
    Blend2D::Blend2D
    navigation_function
    jonathan_contour
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})