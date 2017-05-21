cmake_minimum_required(VERSION 3.8)

project(iso8583core)

file(GLOB_RECURSE sources src/*.cpp)
add_library(${PROJECT_NAME} STATIC ${sources})

enable_testing()
include_directories(unittest)
include_directories(src)

file(GLOB_RECURSE test_sources unittest/*.cpp unittest/*.cc)
add_executable(unittest ${test_sources})
target_link_libraries(unittest iso8583core)