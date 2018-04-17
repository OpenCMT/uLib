
include(uLibMacros)
include_guard(ULIB_TARGET_MACRO_CMAKE)

## adds library target
macro(uLib_add_library name)
  add_library(${name} ${ARGN})
  if(NOT ULIB_INSTALL_NO_LIBRARIES)
    set_property(GLOBAL APPEND PROPERTY ULIB_TARGETS ${name})
  endif(NOT ULIB_INSTALL_NO_LIBRARIES)
endmacro(uLib_add_library)

################################################################################
## Add SHARED library target ##

#  HEADERS and SOURCES must be defined as list of library headers and sources
macro(uLib_add_shared_library name)
 if(COMMAND cmake_policy)
 #  cmake_policy( SET CMP0022 NEW )
 endif(COMMAND cmake_policy)

 set(mname ${PACKAGE_LIBPREFIX}${name})

 if(SOURCES)
  uLib_add_library(${mname} SHARED ${SOURCES})
  set(shared ${ULIB_SHARED_LIBRARIES})
  list(APPEND shared ${mname})
  set(ULIB_SHARED_LIBRARIES ${shared} PARENT_SCOPE)
  source_group("${project_name}\\${name}" FILES ${SOURCES})
  set_target_properties(${mname} PROPERTIES
                      VERSION ${PROJECT_VERSION}
                      SOVERSION ${PROJECT_SOVERSION}
                      INTERFACE_LINK_LIBRARIES "${LIBRARIES}"
                      LINK_INTERFACE_LIBRARIES "${LIBRARIES}"          ## <- ok for cmake from  2.12 ?
                      IMPORTED_LINK_INTERFACE_LIBRARIES "${LIBRARIES}" ## <- breaks cmake after 2.11 ?
#                      PUBLIC_HEADER ""
  )
  debug(LIBRARIES)

  install(TARGETS ${mname}
         EXPORT "${PROJECT_NAME}Targets"
         RUNTIME DESTINATION ${PACKAGE_INSTALL_BIN_DIR} COMPONENT bin
         LIBRARY DESTINATION ${PACKAGE_INSTALL_LIB_DIR} COMPONENT lib
  #         PUBLIC_HEADER DESTINATION ${PACKAGE_INSTALL_INC_DIR} COMPONENT dev
  )
 endif(SOURCES)

 if(HEADERS)
  foreach(header ${HEADERS})
   install(FILES ${header} DESTINATION ${PACKAGE_INSTALL_INC_DIR}/${name})
  endforeach(header)
  endif(HEADERS)

endmacro(uLib_add_shared_library)


################################################################################
## Add Target ##

macro(uLib_add_target name)
    debug(${name})
    add_executable(${name} ${ARGN})
    set_property(GLOBAL APPEND PROPERTY ULIB_TARGETS ${name})

    set(exported ${ULIB_EXPORTED_TARGETS})
    list(APPEND exported ${name})
    set(ULIB_EXPORTED_TARGETS ${exported} PARENT_SCOPE)

    install(TARGETS ${name}
            EXPORT "${PROJECT_NAME}Targets"
            RUNTIME DESTINATION ${PACKAGE_INSTALL_BIN_DIR} COMPONENT bin
           )
ENDMACRO(uLib_add_target)



################################################################################
## TESTS ##

# TESTS and LIBRARIES must be defined
macro(uLib_add_tests name)
 foreach(tn ${TESTS})
  add_executable(${tn} EXCLUDE_FROM_ALL ${tn}.cpp)
  add_test(${tn} ${tn})

  # adds dependencies to all selected modules in uLib
  #  foreach(module ${ULIB_SELECTED_MODULES})
  #   add_dependencies(${tn} ${project_name}${module})
  #  endforeach(module)

  # adds libraries dependencies
  foreach(library ${LIBRARIES})
   target_link_libraries(${tn} ${library})
  endforeach(library)

 endforeach(tn)

 # custom target to compile all tests
 add_custom_target(all-${name}-tests)
 add_dependencies(all-${name}-tests ${TESTS})
endmacro(uLib_add_tests name)


################################################################################
## UTILS ##

# UTILS and LIBRARIES must be defined
macro(uLib_add_utils name)
 foreach(tn ${UTILS})
  add_executable(${tn} ${tn}.cpp)
  install(TARGETS ${tn} RUNTIME DESTINATION bin)

  # adds dependencies to all selected modules in uLib
  #  foreach(module ${ULIB_SELECTED_MODULES})
  #   add_dependencies(${tn} ${project_name}${module})
  #  endforeach(module)

  # adds libraries dependencies
  foreach(library ${LIBRARIES})
   target_link_libraries(${tn} ${library})
  endforeach(library)

 endforeach(tn)

 # custom target to compile all tests
 add_custom_target(all-${name})
 add_dependencies(all-${name} ${UTILS})

endmacro(uLib_add_utils name)






function(get_gcc_compile_flags target out_flags)
    string(TOUPPER "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" name)
    set(flags "${${name}} ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_COMPILER_ARG1}")
    get_target_property(value ${target} COMPILE_FLAGS)
    if (value)
        list(APPEND flags ${value})
    endif()
    get_target_property(value ${target} TYPE)
    get_target_property(value ${target} COMPILE_DEFINITIONS)
    if (value)
        foreach(item ${value})
            list(APPEND flags "-D${item}")
        endforeach()
    endif()
    STRING(TOUPPER "COMPILE_DEFINITIONS_${CMAKE_BUILD_TYPE}" name)
    get_target_property(value ${target} ${name})
    if (value)
        foreach(item ${value})
            list(APPEND flags "-D${item}")
        endforeach()
    endif()
    get_directory_property(value DEFINITIONS)
    if (value)
        list(APPEND flags ${value})
    endif()
    get_directory_property(value INCLUDE_DIRECTORIES)
    if (value)
        foreach(item ${value})
            list(APPEND flags "-I${item}")
        endforeach()
    endif()
    set(${out_flags} ${flags} PARENT_SCOPE)
endfunction()

function(get_gcc_link_flags target out_flags)
    set(flags)
    get_target_property(value ${target} LINK_FLAGS_RELEASE)
    if (value)
        message(STATUS "-> ${flags}")
        list(APPEND flags ${value})
    endif()
    get_directory_property(value LINK_DIRECTORIES)
    if (value)
        message(STATUS "-> ${flags}")
        foreach(item ${value})
            list(APPEND flags "-L${item}")
        endforeach()
    endif()
    message(STATUS "-> ${flags}")
    set(${out_flags} ${flags} PARENT_SCOPE)
endfunction()
