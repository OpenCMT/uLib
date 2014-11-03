# HEADERS
set(HEADERS
                                DetectorChamber.h
                                ExperimentFitEvent.h
                                GeantEvent.h
                                HitMC.h
                                MuonScatter.h
                                MuonEvent.h
                                MuonError.h
                                ChamberHitEvent.h
                                Hit.h
                                LinearFit.h
                                Solid.h
                                Matter.h
                                Scene.h
)


# SOURCES
set(SOURCES
                Solid.cpp
                Scene.cpp
)

set(LIBRARIES
       ${Boost_SERIALIZATION_LIBRARY}
       ${Boost_SIGNALS_LIBRARY}
       ${Boost_PROGRAM_OPTIONS_LIBRARY}
       ${Eigen_LIBRARY}
       ${Geant4_LIBRARIES}
       ${ROOT_LIBRARIES}
       ${PACKAGE_LIBPREFIX}Core
       ${PACKAGE_LIBPREFIX}Math
       ${PACKAGE_LIBPREFIX}Detectors
)

uLib_add_shared_library(${uLib-module})
add_subdirectory(testing)
