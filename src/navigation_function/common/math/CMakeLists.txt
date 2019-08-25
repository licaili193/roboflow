cmake_minimum_required(VERSION 3.1.0)

project(math)

add_library(navigation_function_math
    Transform.cpp
    DestinationFunction.cpp
    BubbleDestinationFunction.cpp
    Sphere.cpp
)
target_include_directories(navigation_function_math
    PUBLIC ${EIGEN_DIR}
)
target_link_libraries(navigation_function_math 
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})