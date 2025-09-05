set(HEADERS MuonScatter.h MuonError.h MuonEvent.h)

set(ULIB_SELECTED_MODULES ${ULIB_SELECTED_MODULES} Detectors PARENT_SCOPE)


install(FILES ${HEADERS}
        DESTINATION ${INSTALL_INC_DIR}/Detectors)
