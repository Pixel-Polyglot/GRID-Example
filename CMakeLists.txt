cmake_minimum_required(VERSION 3.7)

project(GRID-Example LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -m64")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

link_directories(deps/libs/GRID)
include_directories(deps/include src/headers)
file(GLOB_RECURSE SOURCES src/*.cpp)

add_library(GRID-Example SHARED ${SOURCES})

target_link_libraries(GRID-Example GRID-Core -static-libgcc -static-libstdc++)