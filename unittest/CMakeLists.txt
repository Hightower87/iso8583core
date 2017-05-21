include(ExternalProject)
enable_testing()

project(iso8583_test)
#include_directories(${CMAKE_SOURCE_DIR}/unittest)
include_directories(${CMAKE_SOURCE_DIR}/src)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/externals)

ExternalProject_Add(googletest
    GIT_REPOSITORY https://github.com/google/googletest
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

file(GLOB_RECURSE test_sources *.cpp)
add_executable(${PROJECT_NAME} ${test_sources})
add_dependencies(${PROJECT_NAME} googletest)
target_link_libraries(${PROJECT_NAME} gtest gtest_main pthread)
target_link_libraries(${PROJECT_NAME} iso8583core)