cmake_minimum_required(VERSION 3.3)
project(lab1tree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(lab1tree ${SOURCE_FILES})