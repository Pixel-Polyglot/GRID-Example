cmake_minimum_required(VERSION 3.7)

project(GRID-Example LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

if(MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MD")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MDd")
    endif()
endif()

# set(CMAKE_CXX_FLAGS "-Wall")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif()

add_compile_options(-fvisibility=hidden)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# add_definitions(-DEXPORT_SHARED)
# set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

link_directories(deps/libs/GRID)
include_directories(deps/include src/headers)
file(GLOB_RECURSE SOURCES src/*.cpp)

add_library(GRID-Example SHARED ${SOURCES})

target_link_libraries(GRID-Example GRID-Core)