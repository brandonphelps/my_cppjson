
cmake_minimum_required(VERSION 3.0.0)

project(Parser)

set(TARGET main)

subdirs(main_project)

export(TARGETS main FILE ${CMAKE_BINARY_DIR}/cppjsonConfig.cmake)
