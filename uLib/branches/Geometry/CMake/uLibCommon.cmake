include(uLibMacros)
include_guard(ULIB_COMMON_CMAKE)

include(uLibDebugMacro)

## DIRECTORIES -------------------------------------------------------------- ##

set(ULIB_PARENT_PATH "${PROJECT_SOURCE_DIR}")
message(STATUS "Setting uLib parent path to: ${ULIB_PARENT_PATH}")

## Build directories ##
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib CACHE PATH "build path for lib")
mark_as_advanced(LIBRARY_OUTPUT_PATH)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE PATH "build path for binaries")
mark_as_advanced(EXECUTABLE_OUTPUT_PATH)

## Install directories ##
set(PACKAGE_INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(PACKAGE_INSTALL_LIB_DIR lib/${PACKAGE_NAME} CACHE PATH "Installation directory for libraries")
set(PACKAGE_INSTALL_INC_DIR include/${PACKAGE_NAME} CACHE PATH "Installation directory for headers")
set(PACKAGE_INSTALL_DATA_DIR share/${PACKAGE_NAME} CACHE PATH "Installation directory for data files")
if(WIN32 AND NOT CYGWIN)
 set(DEF_INSTALL_CMAKE_DIR CMake)
else()
 set(DEF_INSTALL_CMAKE_DIR lib/cmake/${PACKAGE_NAME})
endif()
set(PACKAGE_INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INC DATA CMAKE)
  set(var PACKAGE_INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
  mark_as_advanced(PACKAGE_INSTALL_${p}_DIR)
  debug(PACKAGE_INSTALL_${p}_DIR)
endforeach()

# add the binary tree to the search path for include files
# so that we will find config.h
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_BINARY_DIR})
include_directories(${SRC_DIR})


## GLOBAL OPTIONS ----------------------------------------------------------- ##

# Set a default build type to RELEASE WITH DEBUG INFO if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_CXX_WARNING_OPTION "" CACHE STRING "Warning level -WAll to verbose all warnings")
set(CMAKE_VERBOSE_MAKEFILE FALSE CACHE STRING "Verbose compile output switch")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x ${CMAKE_CXX_WARNING_OPTION}")




