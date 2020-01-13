#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)
project(RQt)

#----------------------------------------------------------------------------
# Tell CMake where to find the ROOT installation.
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT)

#----------------------------------------------------------------------------
# Qt library
find_package(Qt5Core QUIET)
find_package(Qt5 COMPONENTS Widgets Gui OpenGL REQUIRED)

add_definitions(${QT_DEFINITIONS})
add_definitions(${Qt5Widgets_DEFINITIONS})

#----------------------------------------------------------------------------
# Setup include directory for this project
#
include_directories(${PROJECT_SOURCE_DIR}/RQtApplication
                    ${PROJECT_SOURCE_DIR}/RQtCanvas
                    ${PROJECT_SOURCE_DIR}/RQtWidget
                    ${ROOT_INCLUDE_DIRS}
                    ${Qt5Widgets_INCLUDE_DIRS})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/RQtApplication/*.cpp
                  ${PROJECT_SOURCE_DIR}/RQtCanvas/*.cpp
                  ${PROJECT_SOURCE_DIR}/RQtWidget/*.cpp)

file(GLOB headers ${PROJECT_SOURCE_DIR}/RQtApplication/*.h
                  ${PROJECT_SOURCE_DIR}/RQtCanvas/*.h
                  ${PROJECT_SOURCE_DIR}/RQtWidget/*.h)

qt5_wrap_cpp(MOC_SRC ${headers})

#----------------------------------------------------------------------------
add_library(${PROJECT_NAME} SHARED ${sources} ${MOC_SRC})

# Required on Unix OS family to be able to be linked into shared libraries.
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_link_libraries(${PROJECT_NAME}
        ${ROOT_LIBRARIES}
        ${ROOT_LIBRARY_DIR}/libGui.so
        ${ROOT_LIBRARY_DIR}/libGed.so
        Qt5::Widgets
        Qt5::Gui
        ${QT5ALL_LDFLAGS})

# Expose projetcs's public includes (including Root and Qt5 transitively) to other
# subprojects through cache variable.
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/RQtApplication
                                 ${PROJECT_SOURCE_DIR}/RQtCanvas
                                 ${PROJECT_SOURCE_DIR}/RQtWidget
        CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)