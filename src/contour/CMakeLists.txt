cmake_minimum_required(VERSION 3.1.0)

project(contour)

add_executable(contour_test
    contour_test.cpp
)

target_link_libraries(contour_test 
    Blend2D::Blend2D
)