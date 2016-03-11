cmake_minimum_required(VERSION 2.8)
project(SortingBible)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -g -Wall")
set(SRC_PATH ${PROJECT_SOURCE_DIR}/src)
include_directories(${SRC_PATH})

# add_subdirectory(src)

enable_testing()
add_subdirectory(tests)

