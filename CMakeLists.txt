cmake_minimum_required(VERSION 2.6)

project(MatrixTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#setup some debug flags
if(DEBUG_MODE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O -g")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftree-vectorize") # Not sure if this is really faster.
	if(UNSERTENT_OPTIMIZATIONS)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -funroll-loops")
	endif()

	#GCC only flags, these does not wotk on clang/icc/etc...
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto -pipe")
	endif()
endif()

if(NATIVE_COMPILE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif()

#From marty1885's advice for g++ option

include_directories(include)

add_library(Matrix SHARED src/matrix.cpp)

add_executable(main main.cpp)
target_link_libraries(main Matrix)
