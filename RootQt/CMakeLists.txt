#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)
project(RootQt)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_DEFAULT 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#----------------------------------------------------------------------------
# prevent for in-source building
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed.")
endif ()

#----------------------------------------------------------------------------
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) #This needs to be done universally to any static library

#----------------------------------------------------------------------------
# Configure the components (subprojects)
# NOTE: The order matters! The most independent ones should go first.
#       If A and B really depend on each other, CMake  can build such correctly,
#       if you specify full path to the include directlry
add_subdirectory(RQt)
add_subdirectory(Examples)

#----------------------------------------------------------------------------
message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})