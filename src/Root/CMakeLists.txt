set(HEADERS RootMathDense.h
            RootMuonScatter.h
            RootHitRaw.h)

set(SOURCES ${HEADERS} RootMuonScatter.cpp)

set(LIBRARIES ${ROOT_LIBRARIES}
              ${PACKAGE_LIBPREFIX}Math)

set(libname ${PACKAGE_LIBPREFIX}Root)
set(ULIB_SHARED_LIBRARIES ${ULIB_SHARED_LIBRARIES} ${libname} PARENT_SCOPE)
set(ULIB_SELECTED_MODULES ${ULIB_SELECTED_MODULES} Root PARENT_SCOPE)

add_library(${libname} SHARED ${SOURCES})
set_target_properties(${libname} PROPERTIES
                      VERSION ${PROJECT_VERSION}
                      SOVERSION ${PROJECT_SOVERSION})
target_link_libraries(${libname} ${LIBRARIES})

install(TARGETS ${libname}
        EXPORT "${PROJECT_NAME}Targets"
        RUNTIME DESTINATION ${PACKAGE_INSTALL_BIN_DIR} COMPONENT bin
        LIBRARY DESTINATION ${PACKAGE_INSTALL_LIB_DIR} COMPONENT lib)

install(FILES ${HEADERS} DESTINATION ${PACKAGE_INSTALL_INC_DIR}/Root)


