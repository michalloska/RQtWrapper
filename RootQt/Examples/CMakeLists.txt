#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)
project(rqt_examples)

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

include_directories(
        ${PROJECT_SOURCE_DIR}/Ex1_RQtBasicApp
        ${PROJECT_SOURCE_DIR}/Ex2_RQtCanvas
        ${PROJECT_SOURCE_DIR}/Ex3_RQtEmbededCanvas
        ${PROJECT_SOURCE_DIR}/Ex4_RQtCanvas
        ${RQt_INCLUDE_DIRS}
        ${ROOT_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS})

#----------------------------------------------------------------------------
#----------------------------------------------------------------------------
file(GLOB sources_ex1 ${PROJECT_SOURCE_DIR}/Ex1_RQtBasicApp/*.cpp)
file(GLOB headers_ex1 ${PROJECT_SOURCE_DIR}/Ex1_RQtBasicApp/*.h)
qt5_wrap_cpp(MOC_SRC_EX1 ${headers_ex1})

add_executable(run_rqtbasic ${PROJECT_SOURCE_DIR}/Ex1_RQtBasicApp/main_ex1.cpp ${sources_ex1} ${MOC_SRC_EX1})
target_link_libraries(run_rqtbasic
        RQt
        ${ROOT_LIBRARIES}
        ${ROOT_LIBRARY_DIR}/libGui.so
        ${ROOT_LIBRARY_DIR}/libGed.so
        ${ROOT_LIBRARY_DIR}/libGeom.so
        ${ROOT_LIBRARY_DIR}/libGdml.so
        Qt5::Widgets)

#----------------------------------------------------------------------------
file(GLOB sources_ex2 ${PROJECT_SOURCE_DIR}/Ex2_RQtDualCanvas/*.cpp)
file(GLOB headers_ex2 ${PROJECT_SOURCE_DIR}/Ex2_RQtDualCanvas/*.h)
qt5_wrap_cpp(MOC_SRC_EX2 ${headers_ex2})

add_executable(run_rqtDualCanvas ${PROJECT_SOURCE_DIR}/Ex2_RQtDualCanvas/main_ex2.cpp ${sources_ex2} ${MOC_SRC_EX2})
target_link_libraries(run_rqtDualCanvas
        RQt
        ${ROOT_LIBRARIES}
        ${ROOT_LIBRARY_DIR}/libGui.so
        ${ROOT_LIBRARY_DIR}/libGed.so
        ${ROOT_LIBRARY_DIR}/libGeom.so
        ${ROOT_LIBRARY_DIR}/libGdml.so
        Qt5::Widgets)


##----------------------------------------------------------------------------
file(GLOB sources_ex3 ${PROJECT_SOURCE_DIR}/Ex3_RQtTabView/*.cpp)
file(GLOB headers_ex3 ${PROJECT_SOURCE_DIR}/Ex3_RQtTabView/*.h)
qt5_wrap_cpp(MOC_SRC_EX3 ${headers_ex3})

add_executable(run_rqtTabView ${PROJECT_SOURCE_DIR}/Ex3_RQtTabView/main_ex3.cpp ${sources_ex3} ${MOC_SRC_EX3})
target_link_libraries(run_rqtTabView
        RQt
        ${ROOT_LIBRARIES}
        ${ROOT_LIBRARY_DIR}/libGui.so
        ${ROOT_LIBRARY_DIR}/libGed.so
        ${ROOT_LIBRARY_DIR}/libGeom.so
        ${ROOT_LIBRARY_DIR}/libGdml.so
        Qt5::Widgets)

##----------------------------------------------------------------------------
file(GLOB sources_ex4 ${PROJECT_SOURCE_DIR}/Ex4_RQtMultipleCanvases/*.cpp)
file(GLOB headers_ex4 ${PROJECT_SOURCE_DIR}/Ex4_RQtMultipleCanvases/*.h)
qt5_wrap_cpp(MOC_SRC_EX4 ${headers_ex4})

add_executable(run_rqtMultCanvas ${PROJECT_SOURCE_DIR}/Ex4_RQtMultipleCanvases/main_ex4.cpp ${sources_ex4} ${MOC_SRC_EX4})
target_link_libraries(run_rqtMultCanvas
        RQt
        ${ROOT_LIBRARIES}
        ${ROOT_LIBRARY_DIR}/libGui.so
        ${ROOT_LIBRARY_DIR}/libGed.so
        ${ROOT_LIBRARY_DIR}/libGeom.so
        ${ROOT_LIBRARY_DIR}/libGdml.so
        Qt5::Widgets)

#----------------------------------------------------------------------------
# Add program to the project targets
# NOTE: this avoids the need of typing the program name after make
add_custom_target(examples_execs DEPENDS run_rqtbasic run_rqtDualCanvas run_rqtTabView run_rqtMultCanvas)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX

install(TARGETS run_rqtbasic DESTINATION bin)
install(TARGETS run_rqtDualCanvas DESTINATION bin)
install(TARGETS run_rqtTabView DESTINATION bin)
install(TARGETS run_rqtMultCanvas DESTINATION bin)
