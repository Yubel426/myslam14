cmake_minimum_required(VERSION 3.22)
project(useeigen)

set(CMAKE_CXX_STANDARD 14)

# 添加Eigen头文件
include_directories("/usr/include/eigen3")

add_executable(useeigen main.cpp)
