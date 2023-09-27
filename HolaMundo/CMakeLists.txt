cmake_minimum_required(VERSION 3.26)
project(HolaMundo)

set(CMAKE_CXX_STANDARD 17)

add_executable(HolaMundo main.cpp)
find_package(box2d CONFIG REQUIRED)
target_link_libraries(HolaMundo PRIVATE box2d::box2d)