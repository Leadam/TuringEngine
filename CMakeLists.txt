cmake_minimum_required(VERSION 2.6)
project(turingengine)

add_definitions(-std=c++11)

add_executable(te main.cpp)

target_link_libraries(te armadillo te_graph SDL)

add_subdirectory(graphics)