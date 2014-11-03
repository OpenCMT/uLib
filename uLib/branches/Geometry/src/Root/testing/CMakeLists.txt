# TESTS
set( TESTS
 RootDebugTest
)

set(LIBRARIES
       ${PACKAGE_LIBPREFIX}Core
       ${PACKAGE_LIBPREFIX}Math
       ${PACKAGE_LIBPREFIX}Root
       ${Boost_SERIALIZATION_LIBRARY}
       ${Boost_SIGNALS_LIBRARY}
       ${Boost_PROGRAM_OPTIONS_LIBRARY}
       ${ROOT_LIBRARIES}
)
uLib_add_tests(${uLib-module})
