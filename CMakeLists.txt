
################################################################################
##### CMAKE LISTS ##############################################################
################################################################################

cmake_minimum_required (VERSION 2.6)

execute_process(COMMAND "clear")
message("//////////////////////////////////////////////////////////////////////")
message("/////////////////// CMAKE PJOJECT CONFIGURATION //////////////////////")
message("//////////////////////////////////////////////////////////////////////")

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
include(uLibGenerateRMake)
include(uLibGenerateRPMS)
#include(uLibGenerateDoc)


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
      ltk
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

## SINGLE LIBRARY LINKING ## (work in progress ... )
option(ULIB_SINGLELIBRARY "Link everything to a single library" OFF)
if(ULIB_SINGLELIBRARY) 
# set(modgrp)
# foreach(module ${ULIB_SELECTED_MODULES})
#  set(grpn srcgrp_${module})
#  list(APPEND modgrp ${grpn})
# endforeach(module)
# add_library(${project_name} SHARED ${srcgrp_Core})
endif(ULIB_SINGLELIBRARY)

## UTILITIES ##
add_subdirectory("${SRC_DIR}/utils/make_recipe")


## PKG CONFIG compatible file ----------------------------------------------- ##

set(PKGCONFIG_FILE_ENABLE OFF CACHE BOOL "enable pkg-config file")
if(PKGCONFIG_FILE_ENABLE)
message("/////////// PKG-CONFIG DISTILLER //////////////")
set(PKGCONFIG_FILE_DESTDIR "/lib/pkgconfig/" CACHE PATH "destination path for pkg-config file")
set(PKGCONFIG_LIBS)

message(STATUS "[cflags] ${CMAKE_C_FLAGS}")
message(STATUS "[cxxflags] ${CMAKE_CXX_FLAGS}")

foreach(module ${ULIB_SHARED_LIBRARIES})
set(PKGCONFIG_LIBS "${PKGCONFIG_LIBS} ${CMAKE_LINK_LIBRARY_FLAG}${module}")
endforeach(module)
message(STATUS "[libs] ${PKGCONFIG_LIBS}")

set(PKGCONFIG_FLAGS)
#add_custom_target(Dummy)

# add the executable
uLib_add_target(Dummy test.cpp)
target_link_libraries(Dummy ${PACKAGE_LIBPREFIX}Core)
target_link_libraries(Dummy ${Boost_SERIALIZATION_LIBRARY})
target_link_libraries(Dummy ${Boost_SIGNALS_LIBRARY})
target_link_libraries(Dummy ${Boost_PROGRAM_OPTIONS_LIBRARY})
target_link_libraries(Dummy ${Geant4_LIBRARIES})
target_link_libraries(Dummy ${ROOT_LIBRARIES})
target_link_libraries(Dummy ${VTK_LIBRARIES})

get_gcc_compile_flags(Dummy, gcc_flags_list)
foreach(item ${gcc_flags_list})
 message(STATUS "[gcc cflags] ${item}")
 set(PKGCONFIG_FLAGS "${PKGCONFIG_FLAGS} ${item}")
endforeach(item)
message(STATUS "[includes] ${PKGCONFIG_FLAGS}")

get_gcc_link_flags(Dummy, gcc_flags_list)
foreach(item ${gcc_flags_list})
 message(STATUS "[gcc libs] ${item}")
endforeach(item)

configure_file(
  "${PROJECT_SOURCE_DIR}/CMakePkgConfig.pc.in"
  "${PROJECT_BINARY_DIR}/libmutom-${PACKAGE_VERSION}.pc"
  )
INSTALL_FILES(${PKGCONFIG_FILE_DESTDIR} FILES ${PROJECT_BINARY_DIR}/libmutom-${PACKAGE_VERSION}.pc)

message("///////////////////////////////////////////")
endif(PKGCONFIG_FILE_ENABLE)





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

# Install the FooBarConfig.cmake and FooBarConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/uLibConfig.cmake"
  "${PROJECT_BINARY_DIR}/uLibConfigVersion.cmake"
  DESTINATION "${PACKAGE_INSTALL_CMAKE_DIR}" COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT "${PROJECT_NAME}Targets" DESTINATION
  "${PACKAGE_INSTALL_CMAKE_DIR}" COMPONENT dev)

install(FILES ${PROJECT_SOURCE_DIR}/ulib.h DESTINATION ${PACKAGE_INSTALL_INC_DIR})



## dummy main executable ---------------------------------------------------- ##

message("Sara's debug....")
message(${ROOT_LIBRARIES})

# add the executable
add_executable(Coretest test.cpp)
target_link_libraries(Coretest ${PACKAGE_LIBPREFIX}Core)
#target_link_libraries(Coretest ${Boost_SERIALIZATION_LIBRARY})
#target_link_libraries(Coretest ${Boost_SIGNALS_LIBRARY})
#target_link_libraries(Coretest ${Boost_PROGRAM_OPTIONS_LIBRARY})
#target_link_libraries(Coretest ${Geant4_LIBRARIES})
target_link_libraries(Coretest ${ROOT_LIBRARIES})
target_link_libraries(Coretest ${VTK_LIBRARIES})

#message( "---------------------------------------------------------------------" )
#execute_process(COMMAND
#                "ls"
##                "cmake --find-package -DNAME=uLib -DLANGUAGE=C -DCOMPILER_ID=GNU -DMODE=COMPILE"
#                )
#message( "---------------------------------------------------------------------" )

## -------------------------------------------------------------------------- ##


# TODO clean also subdirectories
add_custom_target(clean-cmake-files
   COMMAND ${CMAKE_COMMAND} -P ${ULIB_CMAKE_DIR}/clean-all.cmake
)





