cmake_minimum_required(VERSION 3.26)
project(Poligonos_MarcoMorenoAS)

set(CMAKE_CXX_STANDARD 17)

add_executable(Poligonos_MarcoMorenoAS main.cpp)
find_package(box2d CONFIG REQUIRED)
target_link_libraries(Poligonos_MarcoMorenoAS PRIVATE box2d::box2d)
