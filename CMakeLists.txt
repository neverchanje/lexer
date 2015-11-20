cmake_minimum_required(VERSION 3.3)
project(lexer)

# Installs boost library
find_package(Boost REQUIRED)

link_directories(${Boost_LIBRARIES_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

set(CXX_FLAGS
        -Wall
        -Wold-style-cast #warn if C-style implicit-casting occurs
        -Wconversion
)

# GTest will cause recusive setting in CMake when you try to reset the
# location of the clang. So I use the default compiler, Apple Clang here,
# which has slightly differences with official clang.
#
# set(CMAKE_CXX_COMPILER "/usr/local/llvm/bin/clang++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)