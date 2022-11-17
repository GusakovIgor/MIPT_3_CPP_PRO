cmake_minimum_required (VERSION 3.22)

project (Charts VERSION 1.0)


set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED True)

# set (CMAKE_CXX_FLAGS "-ggdb -g -pg -O3")
set (CMAKE_CXX_FLAGS "-O3")

add_subdirectory (Math)
add_subdirectory (Application)
add_subdirectory (Charts)
add_subdirectory (Main)