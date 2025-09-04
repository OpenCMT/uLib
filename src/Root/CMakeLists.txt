set(HEADERS RootMathDense.h
            RootMuonScatter.h
            RootHitRaw.h
            muCastorMCTrack.h
            muCastorHit.h
            muCastorInfo.h
            muCastorSkinHit.h
            muCastorPrimaryVertex.h
            muCastorMuDetDIGI.h
            SkinDetectorWriter.h)

set(SOURCES ${HEADERS} RootMuonScatter.cpp
                       muCastorMCTrack.cpp
                       muCastorHit.cpp
                       muCastorInfo.cpp
                       muCastorSkinHit.cpp
                       muCastorPrimaryVertex.cpp
                       muCastorMuDetDIGI.cpp
                       SkinDetectorWriter.cpp)

set(DICTIONARY_HEADERS muCastorMCTrack.h
                       muCastorHit.h
                       muCastorInfo.h
                       muCastorSkinHit.h
                       muCastorPrimaryVertex.h
                       muCastorMuDetDIGI.h
                       SkinDetectorWriter.h)

set(LIBRARIES ${ROOT_LIBRARIES}
              ${PACKAGE_LIBPREFIX}Math)

set(rDictName ${PACKAGE_LIBPREFIX}RootDict)
root_generate_dictionary(${rDictName} ${DICTIONARY_HEADERS}
                         LINKDEF Linkdef.h)
set_source_files_properties(${rDictName}.cxx
                            PROPERTIES GENERATED TRUE)
set_source_files_properties(${rDictName}.h
                            PROPERTIES GENERATED TRUE)
list(APPEND SOURCES ${rDictName}.cxx)

# TODO use a custom target linked to root_generate_dictionary
set(R_ARTIFACTS ${CMAKE_CURRENT_BINARY_DIR}/lib${rDictName}_rdict.pcm
                ${CMAKE_CURRENT_BINARY_DIR}/lib${rDictName}.rootmap)
install(FILES ${R_ARTIFACTS}
        DESTINATION ${PACKAGE_INSTALL_LIB_DIR})

set(libname ${PACKAGE_LIBPREFIX}Root)
set(ULIB_SHARED_LIBRARIES ${ULIB_SHARED_LIBRARIES} ${libname} PARENT_SCOPE)
set(ULIB_SELECTED_MODULES ${ULIB_SELECTED_MODULES} Root PARENT_SCOPE)

add_library(${libname} SHARED ${SOURCES})
set_target_properties(${libname} PROPERTIES
                      VERSION ${PROJECT_VERSION}
                      SOVERSION ${PROJECT_SOVERSION}
                      CXX_STANDARD 17)
target_link_libraries(${libname} ${LIBRARIES})

install(TARGETS ${libname}
        EXPORT "${PROJECT_NAME}Targets"
        RUNTIME DESTINATION ${PACKAGE_INSTALL_BIN_DIR} COMPONENT bin
        LIBRARY DESTINATION ${PACKAGE_INSTALL_LIB_DIR} COMPONENT lib)

install(FILES ${HEADERS} DESTINATION ${PACKAGE_INSTALL_INC_DIR}/Root)


