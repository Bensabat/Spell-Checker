cmake_minimum_required (VERSION 3.9)
project (spell-checker)

# Set default build type to release
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "release")
endif()

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin/${CMAKE_BUILD_TYPE})

add_subdirectory (src)