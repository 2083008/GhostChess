cmake_minimum_required(VERSION 2.8)

project(chess)

#glob_recurse for all sub dirs

file(GLOB SOURCES src/*.cpp src/Stockfish/src/*.cpp src/Stockfish/src/syzygy/*.cpp)

find_package(Qt5Widgets)

set(CMAKE_CXX_FLAGS "-std=c++11 -pthread -g") # c++11 compiler flag

add_executable(main ${SOURCES})

target_link_libraries(main Qt5::Widgets)