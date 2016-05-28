cmake_minimum_required(VERSION 3.3)
project(lab4hc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(lab4hc ${SOURCE_FILES})