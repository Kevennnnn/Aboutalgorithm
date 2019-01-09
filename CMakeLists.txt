cmake_minimum_required(VERSION 3.12)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp MYGraph.h)

add_executable(prim MPrimGraph.cpp)

add_executable(kruskal KruskalGraph.cpp)