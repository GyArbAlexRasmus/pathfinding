cmake_minimum_required(VERSION 3.9)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project (Pathfinder)

#Version
set (Pathfinder_VERSION_MAJOR 0)
set (Pathfinder_VERSION_MINOR 0)
set (Pathfinder_VERSION_REV 1)

#Find Osmium
find_package(Osmium REQUIRED)
include_directories(${OSMIUM_INCLUDE_DIRS})

#Check if Osmium find was successful
if(NOT OSMIUM_FOUND)
    message(WARNING "Libosmium not found!\n")
endif()

add_executable(Pathfinder main.cpp)
