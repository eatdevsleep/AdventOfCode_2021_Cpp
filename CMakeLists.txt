cmake_minimum_required(VERSION 3.22)


#should be in a toolchain file
set(tools /opt/homebrew/Cellar/gcc/11.2.0_3)
set(CMAKE_C_COMPILER ${tools}/bin/gcc-11)
set(CMAKE_CXX_COMPILER ${tools}/bin/g++-11)

#project name
project(Cpp20Examples VERSION 0.1)

## The best way to include something from github, point at a specific archive, it should also use CMake
# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   # Specify the commit you depend on and update it regularly.
#   URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
# )
# FetchContent_MakeAvailable(googletest)

##Can load directly from github source (requires setting up a key though)
#include(ExternalProject)
#ExternalProject_Add(googletest
###  GIT_REPOSITORY    git@github.com:google/googletest.git 
###  GIT_TAG           release-1.11.0 
###)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src build)
