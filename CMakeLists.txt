cmake_minimum_required(VERSION 3.0)

project(dt)

set (FLAGS "-std=c++1z -g")
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${FLAGS})
set (SRC_DIR ./src)
include_directories(${SRC_DIR})

set (SRC_H
  ${SRC_DIR}/defines.h
  ${SRC_DIR}/question.h
  ${SRC_DIR}/tree_node.h
)

set (SRC_CPP
  ${SRC_DIR}/question.cpp
  ${SRC_DIR}/tree_node.cpp
)

add_executable(dt ${SRC_DIR}/dt.cpp ${SRC_H} ${SRC_CPP})
