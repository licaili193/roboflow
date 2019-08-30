cmake_minimum_required(VERSION 3.1.0)

project(navigation_function)

add_subdirectory(math)

add_library(navigation_function
    SphereWorldNavigationFunction.cpp
)
target_include_directories(navigation_function
    PUBLIC ${EIGEN_DIR}
)
target_link_libraries(navigation_function
    navigation_function_math 
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
