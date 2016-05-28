cmake_minimum_required(VERSION 3.5)
project(lab6grd)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(lab6grd ${SOURCE_FILES})