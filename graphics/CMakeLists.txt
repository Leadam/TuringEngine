cmake_minimum_required(VERSION 2.6)
project(turingengine)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})


add_definitions(-std=c++11)

add_library(te_graph SHARED graphics.cpp chart.cpp)

target_link_libraries(te_graph armadillo ${SDL2_LIBRARIES})
