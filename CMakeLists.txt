cmake_minimum_required(VERSION 2.8)
project(Arctan)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp FPNum.cpp FPNum.h arctan.cpp arctan.h)
add_executable(Arctan ${SOURCE_FILES})