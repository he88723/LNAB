cmake_minimum_required(VERSION 2.6)

project(MatrixTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)

add_library(Matrix SHARED src/matrix.cpp)

add_executable(main main.cpp)
target_link_libraries(main Matrix)
