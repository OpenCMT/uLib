


cmake_minimum_required (VERSION 2.6)
project (Tutorial)

set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

set(PARENT_PATH ${PROJECT_SOURCE_DIR})
set(CMAKE_DIR "${PARENT_PATH}/CMake")
set(CMAKE_MODULE_PATH "${PARENT_PATH}/CMake" ${CMAKE_MODULE_PATH})




macro(add_sources)
    file(RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    foreach(_src ${ARGN})
        if(_relPath)
            list (APPEND SRCS "${_relPath}/${_src}")
        else()
            list (APPEND SRCS "${_src}")
        endif()
    endforeach()
    if(_relPath)
        # propagate SRCS to parent directory
        set (SRCS ${SRCS} PARENT_SCOPE)
    endif()
endmacro()


################################################################################
## PKG FIND ##

## EIGEN ##
# option(USE_EIGEN ON) ## REQUIRED
FIND_PACKAGE(Eigen3)

## ROOT ##
option(ULIB_USE_ROOT "Activate use of Root Cint integration" ON)
include(FindROOT)
find_package(ROOT)


## VTK ##
option(ULIB_USE_VTK "Activate use of Vtk Visual Pipelines" ON)
set(VTK_DIR "PATH/TO/VTK/BUILD/DIRECTORY")
mark_as_advanced(VTK_DIR)
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
message(STATUS "VTK included libraries: ${VTK_LIBRARIES}")


################################################################################

include_directories("${PROJECT_SOURCE_DIR}/src")
add_subdirectory(src)

#include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
#add_subdirectory (MathFunctions)

################################################################################


# add the executable
add_executable(Tutorial main.cpp)
target_link_libraries (Tutorial ManageFilename ${VTK_LIBRARIES})

install(TARGETS Tutorial
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib/static)

install(DIRECTORY src/ DESTINATION include/CodeLoop
          FILES_MATCHING PATTERN "*.h")
