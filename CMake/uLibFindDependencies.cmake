include(uLibMacros)
include_guard(ULIB_FIND_DEPENDENCIES_CMAKE)

include(uLibDebugMacro)

################################################################################
## PKG FIND ##
message("/////////// LOOKING FOR EXTERNAL PACKAGES //////////////")

## BOOST ##
message(STATUS "## BOOST ##")
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.45.0 COMPONENTS
       serialization
       signals
       program_options
REQUIRED)

if(Boost_FOUND)
 set(HAVE_BOOST true)
endif(Boost_FOUND)
include_directories(${Boost_INCLUDE_DIRS})

## OPEN MP ##
message(STATUS "## OPEN MP ##")
find_package(OpenMP)
option(OpenMP_ACTIVE "Activate OpenMP parallel compilation" ON)
if(OPENMP_FOUND AND OpenMP_ACTIVE)
 set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}" )
endif(OPENMP_FOUND AND OpenMP_ACTIVE)

## EIGEN ##
message(STATUS "## EIGEN ##")
# option(USE_EIGEN ON) ## REQUIRED
find_package(Eigen3 REQUIRED)
debug(EIGEN3_INCLUDE_DIR)
include_directories(${EIGEN3_INCLUDE_DIR})

## ROOT ##
message(STATUS "## ROOT ##")
option(ULIB_USE_ROOT "Activate use of Root integration" ON)
### <<<--- ROOT IS REQUIRED FOR THE MOMENT ###
#if(ULIB_USE_ROOT)
include(FindROOTv6)
find_package(ROOT REQUIRED)
if(ROOT_FOUND)
 set(HAVE_ROOT true)
 include_directories(${ROOT_INCLUDE_DIR})
 link_directories(${ROOT_LIBRARY_DIR})
 debug(ROOT_INCLUDE_DIR)
 debug(ROOT_LIBRARY_DIR)
 debug(ROOT_LIBRARIES)
else()
 message(WARNING "Root not found")
endif(ROOT_FOUND)
#endif(ULIB_USE_ROOT)


## VTK ##
option(ULIB_USE_VTK "Activate use of Vtk Visual Pipelines" ON)
if(ULIB_USE_VTK)
 message(STATUS "## VTK ##")
 message(STATUS "Looking for VTK...")
 set(VTK_DIR "PATH/TO/VTK/BUILD/DIRECTORY")
 mark_as_advanced(VTK_DIR)
 find_package(VTK REQUIRED)
 include(${VTK_USE_FILE})
 #message(STATUS "VTK included libraries: ${VTK_LIBRARIES}")
 debug(VTK_USE_FILE)
 debug(VTK_INCLUDE_DIRS)
 debug(VTK_LIBRARY_DIRS)
 debug(VTK_LIBRARIES)
# get_directory_property(compile_def COMPILE_DEFINITIONS)
# debug(compile_def)
endif(ULIB_USE_VTK)


## GEANT ##
option(ULIB_USE_GEANT4 "Activate use of GEANT Integration" ON)
message(STATUS "## GEANT 4 ##")
#include(FindGEANT4) # disabled using system finder
find_package(Geant4)
set(GEANT4_FOUND Geant4_DIR)
if(GEANT4_FOUND AND ULIB_USE_GEANT4)
 message(STATUS "Looking for Geant4... - Geant4 found in ${Geant4_DIR}")
 set(HAVE_GEANT4 true)
 include_directories(${Geant4_INCLUDE_DIRS})         # Add -I type paths
 add_definitions(${Geant4_DEFINITIONS})              # Add -D type defs
 debug_package(Geant4)
endif(GEANT4_FOUND AND ULIB_USE_GEANT4)

## QT4 ##
option(ULIB_USE_QT4 "Activate use of Qt Framework" ON)
if(ULIB_USE_QT4)
 message(STATUS "## QT4 ##")
 find_package(Qt4)
# include_directories(${Qt4_INCLUDE_DIRS})
# debug(Qt4_INCLUDE_DIRS)
endif(ULIB_USE_QT4)

## QT5 ##
option(ULIB_USE_QT5 "Activate use of Qt Framework" ON)
if(ULIB_USE_QT5)
 message(STATUS "## QT5 ##")
 find_package(Qt5Widgets)
# include_directories(${Qt5_INCLUDE_DIRS})
# debug(Qt5_INCLUDE_DIRS)
endif(ULIB_USE_QT5)

## READLINE ##
message(STATUS "## READLINE ##")
find_package(ReadLine)
include_directories(${READLINE_INCLUDE_DIR})
debug(READLINE_INCLUDE_DIR)

## STD MATH REQUIRED ##
#message(STATUS "## STD MATH ##")
set(CMAKE_REQUIRED_INCLUDES CMAKE_REQUIRED_INCLUDES math.h)
set(CMAKE_REQUIRED_LIBRARIES CMAKE_REQUIRED_LIBRARIES m)



################################################################################
