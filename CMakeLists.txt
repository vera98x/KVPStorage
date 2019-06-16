# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)

# Add executable
add_executable(KVPStorage main.cpp container.cpp container.hpp)


# Project's name
project(clay)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

find_package(PkgConfig REQUIRED)

pkg_check_modules(JSONCPP jsoncpp)

link_libraries(${JSONCPP_LIBRARIES})

target_link_libraries(KVPStorage ${JSONCPP_LIBRARIES})

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")
