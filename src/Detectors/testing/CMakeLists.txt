# TESTS
set( TESTS
            GDMLSolidTest
            HierarchicalEncodingTest
)

#set(LIBRARIES
#       ${PACKAGE_LIBPREFIX}Core
#       ${PACKAGE_LIBPREFIX}Math
#       ${PACKAGE_LIBPREFIX}Detectors
#       ${Boost_SERIALIZATION_LIBRARY}
#       ${Boost_SIGNALS_LIBRARY}
#       ${Boost_PROGRAM_OPTIONS_LIBRARY}
#       ${Eigen_LIBRARY}
#       ${Geant4_LIBRARIES}
#       ${ROOT_LIBRARIES}
#)
uLib_add_tests(${uLib-module})
