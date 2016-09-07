cmake_minimum_required(VERSION 2.6)

project(MatrixTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

include_directories(include)

add_executable(main main.cpp)
