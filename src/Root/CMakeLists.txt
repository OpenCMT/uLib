set(HEADERS
 TestTObject.h
 RootMathDense.h
 RootMuonScatter.h
 RootHitRaw.h
 muBlastHit.h
 muBlastMCTrack.h
 muCastorMCTrack.h
 muCastorHit.h
)

set(DICTIONARY_HEADERS
 TestTObject.h
 RootMathDense.h
 RootMuonScatter.h
 RootHitRaw.h
 muBlastHit.h
 muBlastMCTrack.h
 muCastorMCTrack.h
 muCastorHit.h
)

SET(SOURCES
 TestTObject.cpp
 RootMuonScatter.cpp
 muBlastHit.cpp
 muBlastMCTrack.cpp
 muCastorMCTrack.cpp
 muCastorHit.cpp
)

set(LIBRARIES
#       ${Boost_SERIALIZATION_LIBRARY}
#       ${Boost_SIGNALS_LIBRARY}
#       ${Boost_PROGRAM_OPTIONS_LIBRARY}
       ${ROOT_LIBRARIES}
       ${PACKAGE_LIBPREFIX}Core
       ${PACKAGE_LIBPREFIX}Math
)

include(FindROOTv6)
root_generate_dictionary(uLibRootDict ${DICTIONARY_HEADERS} LINKDEF Linkdef.h)
set_source_files_properties(uLibRootDict.cxx PROPERTIES GENERATED TRUE)
set_source_files_properties(uLibRootDict.h PROPERTIES GENERATED TRUE)
list(APPEND SOURCES     uLibRootDict.cxx)


uLib_add_shared_library(${uLib-module})
add_subdirectory(testing)
