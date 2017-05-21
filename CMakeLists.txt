cmake_minimum_required(VERSION 3.8)
project(iso8583core)

file(GLOB_RECURSE sources src/*.cpp)
add_library(${PROJECT_NAME} STATIC ${sources})

add_subdirectory(unittest)