cmake_minimum_required(VERSION 2.8)

project(chess)

#glob_recurse for all sub dirs

file(GLOB SOURCES src/*.cpp)

set(CMAKE_CXX_FLAGS "-std=c++11") # c++11 compiler flag

add_executable(chess ${SOURCES})