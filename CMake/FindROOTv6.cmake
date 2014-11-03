# - Finds ROOT instalation
# This module sets up ROOT information 
# It defines:
# ROOT_FOUND          If the ROOT is found
# ROOT_INCLUDE_DIR    PATH to the include directory
# ROOT_LIBRARIES      Most common libraries
# ROOT_LIBRARY_DIR    PATH to the library directory 
#
# Updated by K. Smith (ksmith37@nd.edu) to properly handle
#  dependncies in ROOT_GENERATE_DICTIONARY

set(ROOT_ROOTSYS $ENV{ROOTSYS} CACHE PATH "path of root installation")


unset(ROOT_CONFIG_EXECUTABLE CACHE)
find_program(ROOT_CONFIG_EXECUTABLE root-config
  PATHS ${ROOT_ROOTSYS}/bin NO_DEFAULT_PATH)

if(NOT ROOT_CONFIG_EXECUTABLE)
  set(ROOT_FOUND FALSE)
else()    
  set(ROOT_FOUND TRUE)

  execute_process(
    COMMAND ${ROOT_CONFIG_EXECUTABLE} --prefix 
    OUTPUT_VARIABLE ROOTSYS 
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  execute_process(
    COMMAND ${ROOT_CONFIG_EXECUTABLE} --version 
    OUTPUT_VARIABLE ROOT_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  execute_process(
    COMMAND ${ROOT_CONFIG_EXECUTABLE} --incdir
    OUTPUT_VARIABLE ROOT_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  execute_process(
    COMMAND ${ROOT_CONFIG_EXECUTABLE} --libs
    OUTPUT_VARIABLE ROOT_LIBRARIES
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  #set(ROOT_LIBRARIES ${ROOT_LIBRARIES} -lThread -lMinuit -lHtml -lVMC -lEG -lGeom -lTreePlayer -lXMLIO -lProof)
  #set(ROOT_LIBRARIES ${ROOT_LIBRARIES} -lProofPlayer -lMLP -lSpectrum -lEve -lRGL -lGed -lXMLParser -lPhysics)
  set(ROOT_LIBRARY_DIR ${ROOTSYS}/lib)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ROOT DEFAULT_MSG ROOT_CONFIG_EXECUTABLE
    ROOTSYS ROOT_VERSION ROOT_INCLUDE_DIR ROOT_LIBRARIES    ROOT_LIBRARY_DIR)

mark_as_advanced(ROOT_CONFIG_EXECUTABLE)

include(CMakeParseArguments)
unset(ROOT_CINT_EXECUTABLE CACHE)
find_program(ROOT_CINT_EXECUTABLE rootcint PATHS ${ROOT_ROOTSYS}/bin NO_DEFAULT_PATH )
mark_as_advanced(ROOT_CINT_EXECUTABLE)


unset(ROOT_GENREFLEX_EXECUTABLE CACHE)
find_program(ROOT_GENREFLEX_EXECUTABLE genreflex PATHS ${ROOT_ROOTSYS}/bin NO_DEFAULT_PATH)
mark_as_advanced(ROOT_GENREFLEX_EXECUTABLE)

find_package(GCCXML)

include(uLibDebugMacro)
#----------------------------------------------------------------------------
# function ROOT_GENERATE_DICTIONARY( dictionary
#                                    header1 header2 ...
#                                    LINKDEF linkdef1 ...
#                                    OPTIONS opt1...)
function(ROOT_GENERATE_DICTIONARY dictionary)
  CMAKE_PARSE_ARGUMENTS(ARG "" "" "LINKDEF;OPTIONS" "" ${ARGN})
  message(" -- generating rootcint dictionary --------------------------------------- ")
  #---Get the list of include directories------------------
  get_directory_property(incdirs INCLUDE_DIRECTORIES)
  set(includedirs)
  foreach( d ${incdirs})
        set(includedirs ${includedirs} -I${d})
  endforeach()
  #---Get the list of header files-------------------------
  set(headerfiles)
  foreach(fp ${ARG_UNPARSED_ARGUMENTS})
      find_file(headerFile ${fp} PATHS ${incdirs})
      set(headerfiles ${headerfiles} ${headerFile})
      debug(headerFile)
      unset(headerFile CACHE)
  endforeach()
  #---Get LinkDef.h file------------------------------------
  set(linkdefs)
  foreach( f ${ARG_LINKDEF})
    find_file(linkFile ${f} PATHS ${incdirs})
    set(linkdefs ${linkdefs} ${linkFile})
    debug(linkdefs)
    unset(linkFile CACHE)
  endforeach()
  #---call rootcint------------------------------------------
  add_custom_command(OUTPUT ${dictionary}.cxx ${dictionary}.h
                     COMMAND ${ROOT_CINT_EXECUTABLE} -cint -f  ${dictionary}.cxx
                             -c -p ${ARG_OPTIONS} ${includedirs} ${headerfiles} ${linkdefs}
                     DEPENDS ${headerfiles} ${linkdefs} VERBATIM)
  message(" -- ---------------------------------------------------------------------- ")
endfunction()

#----------------------------------------------------------------------------
# function REFLEX_GENERATE_DICTIONARY(dictionary   
#                                     header1 header2 ... 
#                                     SELECTION selectionfile ... 
#                                     OPTIONS opt1...)
function(REFLEX_GENERATE_DICTIONARY dictionary)  
  CMAKE_PARSE_ARGUMENTS(ARG "" "" "SELECTION;OPTIONS" "" ${ARGN})
  #---Get the list of header files-------------------------
  set(headerfiles)
  foreach(fp ${ARG_UNPARSED_ARGUMENTS})
    file(GLOB files ${fp})
    if(files)
      foreach(f ${files})
        set(headerfiles ${headerfiles} ${f})
      endforeach()
    else()
      set(headerfiles ${headerfiles} ${fp})
    endif()
  endforeach()
  #---Get Selection file------------------------------------
  if(IS_ABSOLUTE ${ARG_SELECTION})
    set(selectionfile ${ARG_SELECTION})
  else() 
    set(selectionfile ${CMAKE_CURRENT_SOURCE_DIR}/${ARG_SELECTION})
  endif()
  #---Get the list of include directories------------------
  get_directory_property(incdirs INCLUDE_DIRECTORIES)
  set(includedirs) 
  foreach( d ${incdirs})    
    set(includedirs ${includedirs} -I${d})
  endforeach()
  #---Get preprocessor definitions--------------------------
  get_directory_property(defs COMPILE_DEFINITIONS)
  foreach( d ${defs})    
   set(definitions ${definitions} -D${d})
  endforeach()
  #---Nanes and others---------------------------------------
  set(gensrcdict ${dictionary}.cpp)
  if(MSVC)
    set(gccxmlopts "--gccxmlopt=\"--gccxml-compiler cl\"")
  else()
    #set(gccxmlopts "--gccxmlopt=\'--gccxml-cxxflags -m64 \'")
    set(gccxmlopts)
  endif()  
  #set(rootmapname ${dictionary}Dict.rootmap)
  #set(rootmapopts --rootmap=${rootmapname} --rootmap-lib=${libprefix}${dictionary}Dict)
  #---Check GCCXML and get path-----------------------------
  if(GCCXML)
    get_filename_component(gccxmlpath ${GCCXML} PATH)
  else()
    message(WARNING "GCCXML not found. Install and setup your environment to find 'gccxml' executable")
  endif()
  #---Actual command----------------------------------------
  add_custom_command(OUTPUT ${gensrcdict} ${rootmapname}     
                     COMMAND ${GENREFLEX_EXECUTABLE} ${headerfiles} -o ${gensrcdict} ${gccxmlopts} ${rootmapopts} --select=${selectionfile}
                             --gccxmlpath=${gccxmlpath} ${ARG_OPTIONS} ${includedirs} ${definitions}
                     DEPENDS ${headerfiles} ${selectionfile})
endfunction()
  
