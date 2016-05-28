cmake_minimum_required(VERSION 3.3)
project(lab3contest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(lab3contest ${SOURCE_FILES})