# CMake File for VVVVVV
# Written by Ethan "flibitijibibo" Lee
cmake_minimum_required(VERSION 3.10.2)


set(proj_name VVVVVV)
project( ${proj_name}   VERSION 0.1
                        DESCRIPTION "Make Own 3D Engine"
                        LANGUAGES CXX C
)

# C++ settings
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR} )
SET( LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR} )

add_subdirectory(src)
add_subdirectory(new)
add_subdirectory(tests)
add_subdirectory(googletest)
