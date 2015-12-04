project(logger)

cmake_minimum_required(VERSION 3.2)

# Installs boost library
find_package(Boost COMPONENTS thread unit_test_framework REQUIRED)
link_directories(${Boost_LIBRARIES_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

set(CXX_FLAGS
        -Wall
        -Wold-style-cast #warn if C-style implicit-casting occurs
        -Wconversion
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

SET(LOOGGER_HDR
        DataOutput.h
        FixedBuffer.h
        Logger.h
        Fmt.h
        ThisThread.h
        TimeValue.h
)

set(LOGGER_SRC
        DataOutput.cc
        Logger.cc
        TimeValue.cc
)

add_library(logger
        ${LOGGER_SRC}
        ${LOGGER_HDR}
)
target_link_libraries(logger ${Boost_LIBRARIES})

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(tests)