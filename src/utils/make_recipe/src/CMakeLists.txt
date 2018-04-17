################################################################################
################################################################################
################################################################################

cmake_minimum_required(VERSION 2.6)
project(hello_world)
set(SOURCES
    # put your sources here
    main.cpp
)

set(DICTIONARY_HEADERS
    # put dictionary headers here
)

################################################################################
################################################################################
################################################################################
################################################################################
################################################################################


list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake")
include(uLibDebugMacro)
include(uLibCommon)
include(uLibFindDependencies)
include(uLibConfigHeader)
include(uLibGenerateRMake)


## MUDULE FIND PACKAGE ------------------------------------------------------ ##
#find_package(uLib REQUIRED) # not working at the moment

## CONFIG FIND PACKAGE ------------------------------------------------------ ##
#set(CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}/lib/cmake")
unset(ULIB_CONFIG)
find_package(ULIB 0.2 CONFIG
             NAMES uLib
             PATH_SUFFIXES mutom-0.2
)
if(ULIB_CONFIG)
 set(ULIB_FOUND true)
endif()

unset(IB_CONFIG)
find_package(IB 0.2 CONFIG
             PATH_SUFFIXES mutom-0.2
)
if(IB_CONFIG)
 set(IB_FOUND true)
endif()


## PROJECT EXECUTABLE ------------------------------------------------------- ##
add_executable(${PROJECT_NAME} ${SOURCES})

if(ULIB_FOUND)
 include_directories(${ULIB_INCLUDE_DIRS})
 target_link_libraries(${PROJECT_NAME}
    ############################################################################
    ## ULIB MODULES ##
         mutomCore
         mutomMath
         mutomDetectors
    #     mutomVtk
    ############################################################################

    ############################################################################
    #    MANUAL INLCLUDE EXTERNAL DEPENDENCIES
    #    ${Boost_SERIALIZATION_LIBRARY}
    #    ${Boost_SIGNALS_LIBRARY}
    #    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    #    ${Geant4_LIBRARIES}
    #    ${ROOT_LIBRARIES}
    #    ${VTK_LIBRARIES} # all VTK libs
    ############################################################################
)
endif(ULIB_FOUND)

if(IB_FOUND)
 include_directories(${IB_INCLUDE_DIRS})
 target_link_libraries(${PROJECT_NAME} mutomIB )
endif()


## ROOT DICTIONARY COMPILE -------------------------------------------------- ##
if(ROOT_FOUND AND DICTIONARY_HEADERS)
include(FindROOTv6)
message("----------- Building Root Dictionary ----------")
debug(DICTIONARY_HEADERS)
debug(ROOT_CINT_EXECUTABLE)
add_library(dictionary STATIC RootDict.cxx)
add_custom_command(OUTPUT RootDict.cxx RootDict.h
                  COMMAND ${ROOT_CINT_EXECUTABLE} -f RootDict.cxx -c -p ${DICTIONARY_HEADERS} Linkdef.h
)
#root_generate_dictionary(RootDict ${DICTIONARY_HEADERS} LINKDEF Linkdef.h)
set_source_files_properties(RootDict.cxx PROPERTIES GENERATED TRUE)
set_source_files_properties(RootDict.h PROPERTIES GENERATED TRUE)
target_link_libraries(${PROJECT_NAME} dictionary)
endif(ROOT_FOUND AND DICTIONARY_HEADERS)




