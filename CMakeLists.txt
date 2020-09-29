
################################################################################
##### CMAKE LISTS ##############################################################
################################################################################

cmake_minimum_required (VERSION 2.6)

## -------------------------------------------------------------------------- ##

project(uLib)

# The version number.
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 4)
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
set(PROJECT_SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

set(PACKAGE_VERSION   ${PROJECT_VERSION})
set(PACKAGE_NAME      "mutom-${PROJECT_VERSION}" CACHE STRING "name of the package defined inside code (config.h)")
set(PACKAGE_LIBPREFIX "mutom" CACHE STRING "suffix for each library component name")
set(PACKAGE_URL "http:://mutom.pd.infn.it" CACHE STRING "url of the project")
set(PACKAGE_AUTHOR "Andrea Rigoni Garola <andrea.rigoni@pd.infn.it>")


## MACROS ------------------------------------------------------------------- ##

set(ULIB_CMAKE_DIR "${PROJECT_SOURCE_DIR}/CMake")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})
message(STATUS "Project name = ${PROJECT_NAME}")
message(STATUS "Package name = ${PACKAGE_NAME}")
message(STATUS "Package version = ${PACKAGE_VERSION}")
message(STATUS "Module path = ${CMAKE_MODULE_PATH}")

## GLOBALS ------------------------------------------------------------------ ##

set(PACKAGE_INSTALL_BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin 
    CACHE PATH "Installation directory for executables")
set(PACKAGE_INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib/
    CACHE PATH "Installation directory for libraries")
set(PACKAGE_INSTALL_INC_DIR ${CMAKE_INSTALL_PREFIX}/include/${PACKAGE_NAME}
    CACHE PATH "Installation directory for headers")
set(PACKAGE_INSTALL_DATA_DIR ${CMAKE_INSTALL_PREFIX}/share/${PACKAGE_NAME}
    CACHE PATH "Installation directory for data files")
set(PACKAGE_INSTALL_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/lib/cmake/${PACKAGE_NAME}
    CACHE PATH "Installation directory for CMake files")

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
    set(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-as-needed")
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY 
               STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_CXX_WARNING_OPTION "" 
    CACHE STRING "Warning level -WAll to verbose all warnings")
set(CMAKE_VERBOSE_MAKEFILE FALSE
    CACHE STRING "Verbose compile output switch")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x ${CMAKE_CXX_WARNING_OPTION}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -UULIB_SERIALIZATION_ON")

#enable_testing()

## FIND PACKAGES ------------------------------------------------------------ ##

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(Eigen3 CONFIG REQUIRED)
include(${EIGEN3_USE_FILE})

find_package(ROOT CONFIG REQUIRED)
include(${ROOT_USE_FILE})

find_package(VTK CONFIG REQUIRED)
include(${VTK_USE_FILE})

set(CMAKE_REQUIRED_INCLUDES CMAKE_REQUIRED_INCLUDES math.h)
set(CMAKE_REQUIRED_LIBRARIES CMAKE_REQUIRED_LIBRARIES m)

## CONFIG ------------------------------------------------------------------- ##

set(BOOST_PP_VARIADICS ON)

include(CheckIncludeFiles)
include(CheckFunctionExists)
include(CheckSymbolExists)

CHECK_INCLUDE_FILES(inittypes.h HAVE_INITTYPES_H)
CHECK_INCLUDE_FILES(stdbool.h HAVE_STDBOOL_H)
CHECK_INCLUDE_FILES(stdint.h HAVE_STDINT_H)
CHECK_INCLUDE_FILES(stdlib.h HAVE_STDLIB_H)
CHECK_INCLUDE_FILES(dlfcn.h HAVE_DLFCN_H)
CHECK_INCLUDE_FILES(malloc.h HAVE_MALLOC_H)
CHECK_FUNCTION_EXISTS(malloc HAVE_MALLOC)
CHECK_INCLUDE_FILES(memory.h HAVE_MEMORY_H)
CHECK_INCLUDE_FILES(math.h HAVE_MATH_H)
CHECK_FUNCTION_EXISTS(fsetround HAVE_FSETROUND)
CHECK_FUNCTION_EXISTS(floor HAVE_FLOOR)
CHECK_FUNCTION_EXISTS(pow HAVE_POW)
CHECK_FUNCTION_EXISTS(sqrt HAVE_SQRT)
CHECK_FUNCTION_EXISTS(strdup HAVE_STRDUP)
CHECK_FUNCTION_EXISTS(strstr HAVE_STRSTR)
CHECK_INCLUDE_FILES(strings.h HAVE_STRINGS_H)
CHECK_INCLUDE_FILES(string.h HAVE_STRING_H)
CHECK_INCLUDE_FILES(sys/stat.h HAVE_SYS_STAT_H)
CHECK_INCLUDE_FILES(sys/types.h HAVE_SYS_TYPES_H)
CHECK_INCLUDE_FILES(unistd.h HAVE_UNISTD_H)
CHECK_INCLUDE_FILES(assert.h HAVE_ASSERT_H)

configure_file("${PROJECT_SOURCE_DIR}/CMakeConfig.in.h"
               "${PROJECT_BINARY_DIR}/config.h")

install(FILES "${PROJECT_BINARY_DIR}/config.h"
        DESTINATION ${PACKAGE_INSTALL_INC_DIR})

## ADD LIBRARIES SUBDIRECTORIES --------------------------------------------- ##

include_directories(${PROJECT_BINARY_DIR})
include_directories(${SRC_DIR})

## uLib_add_shared_library puts names there
set(ULIB_SHARED_LIBRARIES)
## select modules ##
set(ULIB_SELECTED_MODULES)

include_directories(${SRC_DIR}/Core)
add_subdirectory(${SRC_DIR}/Core)

include_directories(${SRC_DIR}/Math)
add_subdirectory(${SRC_DIR}/Math)

include_directories(${SRC_DIR}/Detectors)
add_subdirectory(${SRC_DIR}/Detectors)

include_directories(${SRC_DIR}/Root)
add_subdirectory(${SRC_DIR}/Root)

include_directories(${SRC_DIR}/Vtk)
add_subdirectory(${SRC_DIR}/Vtk)

#add_subdirectory("${SRC_DIR}/utils/make_recipe")

## Documentation and packages

#include(uLibGenerateDoc)

## UTILITIES ##
#add_subdirectory("${SRC_DIR}/utils/make_recipe")


## INSTALLS AND EXPORTS ----------------------------------------------------- ##

#export(PACKAGE ULIB)
#export(TARGETS ${ULIB_SHARED_LIBRARIES} ${ULIB_EXPORTED_TARGETS}
#       FILE "${PROJECT_BINARY_DIR}/uLibTargets.cmake"    )


# Create the FooBarConfig.cmake and FooBarConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${PACKAGE_INSTALL_CMAKE_DIR}"
   "${PACKAGE_INSTALL_INC_DIR}")

# ... for the build tree
#set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src" "${PROJECT_BINARY_DIR}")
#configure_file(uLibConfig.cmake.in 
#               "${PROJECT_BINARY_DIR}/uLibConfig.cmake" @ONLY)

# ... for the install tree
set(CONF_INCLUDE_DIRS "\${ULIB_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(uLibConfig.cmake.in
               "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/uLibConfig.cmake"
               @ONLY)

# ... for both
configure_file(uLibConfigVersion.cmake.in
               "${PROJECT_BINARY_DIR}/uLibConfigVersion.cmake" @ONLY)

install(FILES "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/uLibConfig.cmake"
              "${PROJECT_BINARY_DIR}/uLibConfigVersion.cmake"
        DESTINATION "${PACKAGE_INSTALL_CMAKE_DIR}"
        COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT "${PROJECT_NAME}Targets"
        DESTINATION "${PACKAGE_INSTALL_CMAKE_DIR}"
        COMPONENT dev)

