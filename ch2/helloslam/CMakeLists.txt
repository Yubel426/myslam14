cmake_minimum_required(VERSION 3.22)
#创建
project(hello_slam)


set(CMAKE_BUILD_TYPE "Debug")
#创建应用 应用名 应用文件
add_executable(hello_slam main.cpp)

#添加库 库名 库文件 .cpp
add_library(hello libhelloslam.cpp)
#添加共享库
add_library(hello_shared SHARED libhelloslam.cpp)


#       应用名 库名
#target_link_libraries(hello_slam hello)

target_link_libraries(hello_slam hello_shared)

