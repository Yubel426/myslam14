cmake_minimum_required(VERSION 3.22)


set(CMAKE_CXX_STANDARD 14)
include_directories(/usr/include/eigen3)

add_executable(transform Transform.cpp)
