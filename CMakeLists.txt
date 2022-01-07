cmake_minimum_required(VERSION 3.0)

project(japraq)

# Set compiler flags.
set (FLAGS "-std=c++14 -g")
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${FLAGS})

# Tester project.
add_subdirectory(./projects/japraq_tester)

# Simple CLI.
add_subdirectory(./projects/japraq_cli)
