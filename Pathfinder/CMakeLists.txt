cmake_minimum_required(VERSION 3.9)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(Pathfinder)

#Set version
set(Pathfinder_VERSION_MAJOR 0)
set(Pathfinder_VERSION_MINOR 0)
set(Pathfinder_VERSION_REV 1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#Find Osmium and Boost
find_package(Boost REQUIRED COMPONENTS program_options)
find_package(Osmium REQUIRED)

#Include Osmium and Boost
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OSMIUM_INCLUDE_DIRS})

add_executable(Pathfinder src/main.cpp)
target_link_libraries(Pathfinder ${Boost_LIBRARIES})