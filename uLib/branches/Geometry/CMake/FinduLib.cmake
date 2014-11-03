# - Finds ROOT instalation
# This module sets up ROOT information
# It defines:
# ULIB_FOUND          If the uLib is found
# ULIB_INCLUDE_DIRS   PATH to the include directory
# ULIB_LIBRARIES      Most common libraries
# ULIB_LIBRARY_DIRS   PATH to the library directory
#

include(uLibFindDependencies)
include(uLibDebugMacro)

## CONFIG FIND -------------------------------------------------------------- ##

set(CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}/lib/cmake")
unset(ULIB_CONFIG)
find_package(ULIB ${ULIB_PACKAGE_VERSION} CONFIG
             NAMES uLib
             PATH_SUFFIXES ${ULIB_PACKAGE_NAME}
)

debug(ULIB_CONFIG)
debug(ULIB_CONSIDERED_CONFIGS)
debug(ULIB_CONSIDERED_VERSIONS)
debug(ULIB_INCLUDE_DIRS)
debug(ULIB_LIBRARIES)

if(ULIB_CONFIG)
 set(ULIB_FOUND true)
endif()

## MODULE FIND -------------------------------------------------------------- ##

#find_path(uLib_INCLUDE_DIR
#   NAMES ulib.h
#   PATH_SUFFIXES mutom-0.2
#)
#debug(uLib_INCLUDE_DIR)

#find_file(uLib_USE_FILE
#   NAMES uLib_exported_targets.cmake
#   PATHS lib lib64
#   PATH_SUFFIXES mutom-0.2
#)
#debug(uLib_USE_FILE)

#find_library(uLib_LIBRARY
#   NAMES libmutomCore.so
#   PATH_SUFFIXES mutom-0.2
# )
#debug(uLib_LIBRARY)

##set( uLib_PROCESS_INCLUDES uLib_INCLUDE_DIR ULIB_INCLUDE_DIRS )
##set( uLib_PROCESS_LIBS uLib_LIBRARY ULIB_LIBRARIES )
##libfind_process(uLib)

#set( ULIB_INCLUDE_DIRS ${uLib_INCLUDE_DIR} )
#set( ULIB_LIBRARIES ${uLib_LIBRARY} )
#include(FindPackageHandleStandardArgs)
#find_package_handle_standard_args(uLib DEFAULT_MSG
#                                  uLib_LIBRARY uLib_INCLUDE_DIR)
#mark_as_advanced(uLib_INCLUDE_DIR uLib_LIBRARY)
