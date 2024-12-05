project(aoc2024_d1)
cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(common)
set(HEADER_FILES ../common/aoc.h)

file(GLOB dirs LIST_DIRECTORIES true day*)
foreach(dir ${dirs})
  add_subdirectory(${dir})
endforeach()
