
cmake_minimum_required(VERSION 3.0.0)

project(CppJson)

set(TARGET main)

subdirs(main_project)


set(CppJson_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/main_project/include")

message(STATUS "INCLUDE: ${CppJson_INCLUDE_DIR}")
