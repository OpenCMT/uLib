
################################################################################
##### CMAKE LISTS ##############################################################
################################################################################

cmake_minimum_required (VERSION 2.6)

## -------------------------------------------------------------------------- ##

project(uLib)

# The version number.
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 2)
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
message(STATUS "Module path: ${CMAKE_MODULE_PATH}")

include(uLibMacros)
include(uLibDebugMacro)
include(uLibTargetMacros)
#include(uLibGenerateRMake)


## GLOBALS ------------------------------------------------------------------ ##

include(uLibCommon)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ") ## Add flags here ##

enable_testing()

## FIND PACKAGES ------------------------------------------------------------ ##

include(uLibFindDependencies)


## CONFIG ------------------------------------------------------------------- ##

include(uLibConfigHeader)

## ADD LIBRARIES SUBDIRECTORIES --------------------------------------------- ##

## select modules ##
set(ULIB_SELECTED_MODULES
      Core
      Math
      Detectors
      Root
)

## uLib_add_shared_library puts names there
set(ULIB_SHARED_LIBRARIES)

if(ULIB_USE_VTK)
 LIST(APPEND ULIB_SELECTED_MODULES Vtk)
endif(ULIB_USE_VTK)

## Documentation and packages

include(uLibGenerateRPMS)
include(uLibGenerateDoc)

## this gets ulib modules into a variable ##
function(uLib_modules result)
 set(out)
 foreach(module ${ULIB_SELECTED_MODULES})
  list(APPEND out ${PACKAGE_LIBPREFIX}${module})
 endforeach(module)
 set(${result} "${out}" PARENT_SCOPE)
endfunction()


## ENTERING MODULES SUBDIRECTORIES ##
message("/////////// SELECTED MODULES //////////////")
foreach(module ${ULIB_SELECTED_MODULES})
 message(STATUS "adding module: ${module}")
 set( uLib-module ${module})
 include_directories(${SRC_DIR}/${module})
 add_subdirectory(${SRC_DIR}/${module})
endforeach(module)

## UTILITIES ##
add_subdirectory("${SRC_DIR}/utils/make_recipe")


## INSTALLS AND EXPORTS ----------------------------------------------------- ##

#export(PACKAGE uLib)
export(PACKAGE ULIB)
export(TARGETS ${ULIB_SHARED_LIBRARIES} ${ULIB_EXPORTED_TARGETS}
       FILE "${PROJECT_BINARY_DIR}/uLibTargets.cmake"    )
#export(TARGETS ${ULIB_EXPORTED_TARGETS}
#       FILE "${PROJECT_BINARY_DIR}/uLibExeTargets.cmake" )


# Create the FooBarConfig.cmake and FooBarConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${PACKAGE_INSTALL_CMAKE_DIR}"
   "${PACKAGE_INSTALL_INC_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src" "${PROJECT_BINARY_DIR}")
configure_file(uLibConfig.cmake.in
  "${PROJECT_BINARY_DIR}/uLibConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${ULIB_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(uLibConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/uLibConfig.cmake" @ONLY)
# ... for both
configure_file(uLibConfigVersion.cmake.in
               "${PROJECT_BINARY_DIR}/uLibConfigVersion.cmake" @ONLY)

install(FILES "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/uLibConfig.cmake"
              "${PROJECT_BINARY_DIR}/uLibConfigVersion.cmake"
              "${PROJECT_SOURCE_DIR}/CMake/FindReadLine.cmake"
              "${PROJECT_SOURCE_DIR}/CMake/FindROOT.cmake"
              "${PROJECT_SOURCE_DIR}/CMake/FindROOTv6.cmake"
              "${PROJECT_SOURCE_DIR}/CMake/uLibCommon.cmake"
              "${PROJECT_SOURCE_DIR}/CMake/uLibConfigHeader.cmake"
              "${PROJECT_SOURCE_DIR}/CMake/uLibDebugMacro.cmake"
              "${PROJECT_SOURCE_DIR}/CMake/uLibFindDependencies.cmake"
              "${PROJECT_SOURCE_DIR}/CMake/uLibGenerateDoc.cmake"
              "${PROJECT_SOURCE_DIR}/CMake/uLibGenerateRMake.cmake"
              "${PROJECT_SOURCE_DIR}/CMake/uLibGenerateRPMS.cmake"
              "${PROJECT_SOURCE_DIR}/CMake/uLibMacros.cmake"
              "${PROJECT_SOURCE_DIR}/CMake/uLibTargetMacros.cmake"
        DESTINATION "${PACKAGE_INSTALL_CMAKE_DIR}"
        COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT "${PROJECT_NAME}Targets" DESTINATION
  "${PACKAGE_INSTALL_CMAKE_DIR}" COMPONENT dev)

install(FILES ${PROJECT_SOURCE_DIR}/ulib.h DESTINATION ${PACKAGE_INSTALL_INC_DIR})


# TODO clean also subdirectories
add_custom_target(clean-cmake-files
   COMMAND ${CMAKE_COMMAND} -P ${ULIB_CMAKE_DIR}/clean-all.cmake
)





