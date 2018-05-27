cmake_minimum_required(VERSION 3.9)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(Pathfinder VERSION 0.0.1)

#Make sure executable pops out in /bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#Find Osmium and Boost
find_package(Boost REQUIRED COMPONENTS program_options filesystem)

#Include Osmium and Boost
include_directories(${Boost_INCLUDE_DIRS})

#Define version for use in program
add_definitions(-DPATHFINDER_VERSION="${Pathfinder_VERSION}")
add_definitions(-DNDEBUG)

#Get source files
file(GLOB SOURCES src/*.cpp)

add_compile_options(-g3 -O3 -Wall -Wextra)
add_executable(Pathfinder ${SOURCES})
set(CMAKE_CXX_FLAGS -no-pie)

target_link_libraries(Pathfinder ${Boost_LIBRARIES})