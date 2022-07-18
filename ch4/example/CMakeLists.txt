cmake_minimum_required(VERSION 3.22)
project(example)

set(CMAKE_CXX_STANDARD 14)



find_package(Sophus REQUIRED)
find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})
include_directories(${Sophus_INCLUDE_DIRS})
add_executable(example main.cpp)
target_link_libraries(example Sophus::Sophus ${Pangolin_LIBRARIES} )


