cmake_minimum_required(VERSION 3.1.0)

project(gui)

add_subdirectory(drawing)

set(CMAKE_AUTOMOC TRUE)

find_package(Qt5Widgets REQUIRED)

add_executable(remote_viewer
remote_viewer.cpp
    qblcanvas.cpp
)

target_link_libraries(remote_viewer 
    Qt5::Widgets 
    Blend2D::Blend2D
)

qt5_use_modules(remote_viewer 
    Widgets
)

add_executable(canvas_test
    canvas_test.cpp
)

target_link_libraries(canvas_test 
    Blend2D::Blend2D
    drawing_widgets
)