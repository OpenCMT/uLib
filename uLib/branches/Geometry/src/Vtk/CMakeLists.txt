set(HEADERS
                          uLibVtkInterface.h
                          uLibVtkViewer.h
                          vtkContainerBox.h
                          vtkMuonScatter.h
                          vtkStructuredGrid.h
                          vtkVoxRaytracerRepresentation.h
                          vtkVoxImage.h
#                          vtkHLineRepresentation.h
#			  vtkTriangleMesh.h
)

SET(SOURCES
                uLibVtkInterface.cxx
                uLibVtkViewer.cpp
                vtkContainerBox.cpp
                vtkMuonScatter.cxx
                vtkStructuredGrid.cpp
                vtkVoxRaytracerRepresentation.cpp
                vtkVoxImage.cpp
)

set(LIBRARIES
       ${Boost_SERIALIZATION_LIBRARY}
       ${Boost_SIGNALS_LIBRARY}
       ${Boost_PROGRAM_OPTIONS_LIBRARY}
       ${Eigen_LIBRARY}
       ${ROOT_LIBRARIES}
       ${Geant4_LIBRARIES}
       ${VTK_LIBRARIES}
       ${PACKAGE_LIBPREFIX}Core
       ${PACKAGE_LIBPREFIX}Math
       ${PACKAGE_LIBPREFIX}Detectors
       ${PACKAGE_LIBPREFIX}Vtk
)

uLib_add_shared_library(${uLib-module})

add_subdirectory(testing)
